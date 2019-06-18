//
// Created by Khyber on 3/14/2019.
//

#include "BranchCoverageRuntime.h"

#include "src/main/runtime/coverage/include.h"

#include <numeric>

namespace runtime::coverage::branch {
    
    class BranchCoverageRuntime {
    
    private:
        
        static constexpr size_t pageSize = fse::page::constSize;
        
        class Counts {
        
        public:
            
            union {
                
                struct {
                    u64 single;
                    u64 multi;
                    u64 infinite;
                } branches = {};
                
                std::array<u64, 3> all;
                
            };
        
        private:
            
            const io::Writer write;
        
        public:
            
            explicit constexpr Counts(io::Writer&& write) noexcept : all({}), write(std::move(write)) {}
            
            deleteCopy(Counts);
            
            ~Counts() noexcept {
                flush();
            }
            
            void flush() const noexcept {
                write.absolute(all.data(), sizeof(all));
            }
            
        };
        
        class SingleBranches {
        
        private:
            
            using Size = u32;
            using Chunk = u64;
            
            static constexpr Size bufferByteSize = static_cast<Size>(math::lcm(pageSize, sizeof(Chunk)));
            static constexpr Size bufferSize = bufferByteSize / sizeof(Chunk);
//            static constexpr Size bufferBitSize = bufferByteSize * numBits<u8>();
            
            std::array<Chunk, bufferSize> buffer = {};
            Size bitIndex = 0;
            Size bitIndexDiff = 0;
            
            struct shift {
                
                static constexpr Size byte = 3;
                static_assert(1u << byte == numBits<u8>());
                
                static constexpr Size chunk = 6;
                static_assert(1u << chunk == numBits<Chunk>());
                
            };
            
            constexpr Size byteIndex() const noexcept {
                return bitIndex >> shift::byte;
            }
            
            constexpr Size chunkIndex() const noexcept {
                return bitIndex >> shift::chunk;
            }
            
            constexpr u8 byteBitIndex() const noexcept {
                return static_cast<u8>(bitIndex & ((1u << shift::byte) - 1));
            }
            
            constexpr u8 chunkBitIndex() const noexcept {
                return static_cast<u8>(bitIndex & ((1u << shift::chunk) - 1));
            }
        
        public:
            
            Size resetBitIndexDiff() noexcept {
                const auto temp = bitIndexDiff;
                bitIndexDiff = 0;
                return temp;
            }
        
        private:
            
            const io::Writer write;
            
            void writeBuffer(size_t numBytes = sizeof(buffer)) noexcept {
                write(buffer.begin(), numBytes);
            }
            
            void flush() noexcept {
                writeBuffer();
                bitIndex = 0;
            }
            
            constexpr bool shouldFlush() const noexcept {
                return chunkIndex() == buffer.size();
            }
            
            void tryFlush() noexcept {
                if (shouldFlush()) {
                    flush();
                }
            }
            
            void finalFlush() noexcept {
                writeBuffer(math::minBytesForBits(bitIndex));
                const u8 bitsInLastBytes = byteBitIndex();
                write(&bitsInLastBytes, sizeof(bitsInLastBytes));
            }
        
        public:
            
            explicit constexpr SingleBranches(io::Writer&& write) noexcept : write(std::move(write)) {}
            
            deleteCopy(SingleBranches);
            
            ~SingleBranches() noexcept {
                finalFlush();
            }
            
            void on(bool value) noexcept {
                buffer[chunkIndex()] |= static_cast<u64>(value) << chunkBitIndex();
                bitIndex++;
                bitIndexDiff++;
                tryFlush();
            }
            
            SingleBranches& operator<<(bool value) noexcept {
                on(value);
                return *this;
            }
            
        };
        
        class NonSingleBranches {
        
        private:
            
            struct Record {
                u32 bitIndexDiff: 31;
                bool isMultiple: 1;
                u32 low;
                u32 high;
            };
            
            io::WriteBuffer<Record> buffer;
            
            void onRecord(Record record) noexcept {
                buffer << record;
            }
        
        public:
            
            explicit constexpr NonSingleBranches(io::Writer&& write) noexcept : buffer(std::move(write)) {}
            
            deleteCopy(NonSingleBranches);
            
            void onMulti(u32 branchNum, u32 numBranches, u32 bitIndexDiff) noexcept {
                onRecord({
                                 .bitIndexDiff = bitIndexDiff,
                                 .isMultiple = static_cast<u32>(true),
                                 .low = branchNum,
                                 .high = numBranches,
                         });
            }
            
            void onInfinite(u64 address, u32 bitIndexDiff) noexcept {
                onRecord({
                                 .bitIndexDiff = bitIndexDiff,
                                 .isMultiple = static_cast<u32>(false),
                                 .low = static_cast<u32>(address),
                                 .high = static_cast<u32>(address >> 32u),
                         });
            }
            
        };
        
        Counts count;
        
        struct Branches {
            
            SingleBranches single;
            NonSingleBranches nonSingle;
            
            constexpr Branches(io::Writer&& singleWrite, io::Writer&& nonSingleWrite) noexcept
                    : single(std::move(singleWrite)), nonSingle(std::move(nonSingleWrite)) {}
            
        } branches;
    
    public:
        
        void onSingleBranch(bool value) noexcept {
            count.branches.single++;
            branches.single << value;
        }
        
        void onMultiBranch(u32 branchNum, u32 numBranches) noexcept {
            count.branches.multi++;
            branches.nonSingle.onMulti(branchNum, numBranches, branches.single.resetBitIndexDiff());
            count.flush();
        }
        
        void onInfiniteBranch(void* address) noexcept {
            count.branches.infinite++;
            branches.nonSingle.onInfinite(reinterpret_cast<u64>(address), branches.single.resetBitIndexDiff());
            count.flush();
        }
    
    private:
        
        explicit BranchCoverageRuntime(const fse::Dir& dir) noexcept(false)
                : count(writer(dir, "counts")),
                  branches(writer(dir, "single"), writer(dir, "nonSingle")) {}
    
    public:
        
        explicit BranchCoverageRuntime() noexcept(false)
                : BranchCoverageRuntime(output().dir.dir("branch")) {}
        
    };
    
    thread_local auto& rt = LazilyConstructed<BranchCoverageRuntime>::add();
    
}

namespace {
    using runtime::coverage::branch::rt;
}

API_BranchCoverage(onSingleBranch)(bool value) noexcept {
//    printf("BranchCoverage: onBranch: %s\n", value ? "true" : "false");
    API_rt().onSingleBranch(value);
}

API_BranchCoverage(onMultiBranch)(u32 branchNum, u32 numBranches) noexcept {
//    printf("BranchCoverage: onMultiBranch: %d/%d\n", branchNum, numBranches);
    API_rt().onMultiBranch(branchNum, numBranches);
}

API_BranchCoverage(onInfiniteBranch)(void* address) noexcept {
//    printf("BranchCoverage: onInfiniteBranch: %p\n", address);
    API_rt().onInfiniteBranch(address);
}
