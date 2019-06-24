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
            Size bitIndexDiff = 0;
            
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
                
                Average combined;
                Average low;
                Average high;
                Average both;
                
                void print(std::ostream& out) const noexcept {
                    out << '\n';
                    #define _(field) out << ""#field ": " << field << '\n';
                    _(combined);
                    _(low);
                    _(high);
                    _(both);
                    #undef _
                    out << std::endl;
                }
                
            } varintAverages;
            
            struct Record {
                
                union {
                    struct {
                        bool isMultiple: 1;
                        u32 bitIndexDiff: 31;
                    };
                    u32 combined;
                };
                union {
                    struct {
                        u32 low;
                        u32 high;
                    };
                    u64 both;
                };
                
                void print(io::LEB128WriteBuffer& out, VarintAverages& averages) const noexcept {
                    averages.combined << combined;
                    out << combined;
                    if (isMultiple) {
                        averages.low << low;
                        averages.high << high;
                        out << low << high;
                    } else {
                        averages.both << both;
                        out << both;
                    }
//                    averages.combined << out.on(combined);
//                    if (isMultiple) {
//                        averages.low << out.on(low);
//                        averages.high << out.on(high);
//                    } else {
//                        averages.both << out.on(both);
//                    }
                }
                
            };
            
            Counts& counts;
            
            io::LEB128WriteBuffer buffer;
            
            void onRecord(Record record) noexcept {
                static_assert(decltype(buffer.buffer)::size() > sizeof(record) * 2);
                const size_t lastIndex = buffer.buffer.currentIndex();
                record.print(buffer, varintAverages);
                if (buffer.buffer.currentIndex() < lastIndex) {
                    // means buffer was flushed
                    counts.flush();
                }
            }
        
        public:
            
            constexpr NonSingleBranches(Counts& counts, io::Writer&& write) noexcept
                    : counts(counts), buffer(std::move(write)) {}
            
            deleteCopy(NonSingleBranches);
            
            ~NonSingleBranches() {
                counts.flush();
                varintAverages.print(std::cerr);
            }
            
            void onMulti(u32 branchNum, u32 numBranches, u32 bitIndexDiff) noexcept {
                counts.branches.multi++;
                onRecord({
                                 .bitIndexDiff = bitIndexDiff,
                                 .isMultiple = static_cast<u32>(true),
                                 .low = branchNum,
                                 .high = numBranches,
                         });
            }
            
            void onInfinite(u64 address, u32 bitIndexDiff) noexcept {
                counts.branches.infinite++;
                onRecord({
                                 .bitIndexDiff = bitIndexDiff,
                                 .isMultiple = static_cast<u32>(false),
                                 .low = static_cast<u32>(address),
                                 .high = static_cast<u32>(address >> 32u),
                         });
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
        
        void onMultiBranch(u32 branchNum, u32 numBranches) noexcept {
            branches.nonSingle.onMulti(branchNum, numBranches, branches.single.resetBitIndexDiff());
        }
        
        void onInfiniteBranch(void* address) noexcept {
            branches.nonSingle.onInfinite(reinterpret_cast<u64>(address), branches.single.resetBitIndexDiff());
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

API_BranchCoverage(onMultiBranch)(u32 branchNum, u32 numBranches) noexcept {
//    printf("BranchCoverage: onMultiBranch: %d/%d\n", branchNum, numBranches);
    API_rt().onMultiBranch(branchNum, numBranches);
}

API_BranchCoverage(onSwitchCase)(bool valid, u32 caseNum, u32 numCases) noexcept {
    if (valid) {
        __BranchCoverage_onMultiBranch(caseNum, numCases);
    }
}

API_BranchCoverage(onInfiniteBranch)(void* address) noexcept {
//    printf("BranchCoverage: onInfiniteBranch: %p\n", address);
    API_rt().onInfiniteBranch(address);
}
