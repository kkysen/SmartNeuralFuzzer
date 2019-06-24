//
// Created by Khyber on 3/14/2019.
//

#include "BranchCoverageRuntime.h"

#include "src/main/runtime/coverage/include.h"

#include <numeric>
#include <iostream>

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
            
            Counts& counts;
            
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
            
            const io::Writer write;
            
            void writeBuffer(size_t numBytes = sizeof(buffer)) noexcept {
                write(buffer.begin(), numBytes);
                counts.flush();
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
            
            constexpr SingleBranches(Counts& counts, io::Writer&& write) noexcept
                    : counts(counts), write(std::move(write)) {}
            
            deleteCopy(SingleBranches);
            
            ~SingleBranches() noexcept {
                finalFlush();
            }
            
            void on(bool value) noexcept {
                counts.branches.single++;
                buffer[chunkIndex()] |= static_cast<u64>(value) << chunkBitIndex();
                bitIndex++;
                tryFlush();
            }
            
            SingleBranches& operator<<(bool value) noexcept {
                on(value);
                return *this;
            }
            
        };
        
        class NonSingleBranches {
        
        private:
            
            class Average {
            
            private:
                
                f64 total = 0;
                u64 count = 0;
            
            public:
                
                template <typename T>
                constexpr void on(T t) noexcept {
                    total += static_cast<f64>(t);
                    count++;
                }
                
                template <typename T>
                constexpr Average& operator<<(T t) noexcept {
                    on(t);
                    return *this;
                }
                
                constexpr f64 get() const noexcept {
                    return total / count;
                }
                
                /*implicit*/ constexpr operator f64() const noexcept {
                    return get();
                }
                
            };
            
            struct VarintAverages {
                
                Average multi;
                Average infinite;
                
                void print(std::ostream& out) const noexcept {
                    out << '\n';
                    #define _(field) out << ""#field ": " << field << '\n';
                    _(multi);
                    _(infinite);
                    #undef _
                    out << std::endl;
                }
                
            } varintAverages;
            
            Counts& counts;
            
            io::LEB128WriteBuffer buffer;
            
            void tryFlush() noexcept {
                static_assert(decltype(buffer.buffer)::size() > sizeof(u64) * 2);
                const size_t lastIndex = buffer.buffer.currentIndex();
                if (buffer.buffer.currentIndex() < lastIndex) {
                    // means buffer was flushed
                    counts.flush();
                }
            }
            
            static constexpr auto isMulti = static_cast<u32>(true);
        
        public:
            
            constexpr NonSingleBranches(Counts& counts, io::Writer&& write) noexcept
                    : counts(counts), buffer(std::move(write)) {}
            
            deleteCopy(NonSingleBranches);
            
            ~NonSingleBranches() {
                counts.flush();
                varintAverages.print(std::cerr);
            }
            
            void onMulti(u32 branchNum) noexcept {
                counts.branches.multi++;
                varintAverages.multi << branchNum;
                buffer << (isMulti | (branchNum << 1u)); // not simplifiable
                tryFlush();
            }
            
            void onInfinite(u64 address) noexcept {
                counts.branches.infinite++;
                varintAverages.infinite << address;
                // function addresses should be at least bit-aligned
                assert(!(address & isMulti)); // not simplifiable
                buffer << address;
                tryFlush();
            }
            
        };
        
        struct Branches {
            
            Counts count;
            SingleBranches single;
            NonSingleBranches nonSingle;
            
            explicit Branches(const fse::Dir& dir) noexcept
                    : count(writer(dir, "counts")),
                      single(count, writer(dir, "single")),
                      nonSingle(count, writer(dir, "nonSingle")) {}
            
        } branches;
    
    public:
        
        void onSingleBranch(bool value) noexcept {
            branches.single << value;
        }
        
        void onMultiBranch(u32 branchNum) noexcept {
            branches.nonSingle.onMulti(branchNum);
        }
        
        void onInfiniteBranch(void* address) noexcept {
            branches.nonSingle.onInfinite(reinterpret_cast<u64>(address));
        }
        
        explicit BranchCoverageRuntime() noexcept(false)
                : branches(output().dir.dir("branch")) {}
        
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

API_BranchCoverage(onMultiBranch)(u32 branchNum) noexcept {
//    printf("BranchCoverage: onMultiBranch: %d\n", branchNum);
    API_rt().onMultiBranch(branchNum);
}

API_BranchCoverage(onSwitchCase)(bool valid, u32 caseNum) noexcept {
    if (valid) {
        __BranchCoverage_onMultiBranch(caseNum);
    }
}

API_BranchCoverage(onInfiniteBranch)(void* address) noexcept {
//    printf("BranchCoverage: onInfiniteBranch: %p\n", address);
    API_rt().onInfiniteBranch(address);
}
