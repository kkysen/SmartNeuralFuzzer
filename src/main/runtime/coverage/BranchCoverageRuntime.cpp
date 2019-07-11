//
// Created by Khyber on 3/14/2019.
//

#include "src/main/runtime/coverage/BranchCoverageRuntime.h"

#include "src/main/runtime/coverage/include.h"
#include "src/share/io/BoolWriteBuffer.h"

#include <numeric>
#include <iostream>

namespace {
    
    thread_local bool inUntracedCode = false;
    
}

namespace runtime::coverage::branch {
    
    class BranchCoverageRuntime {
    
    private:
        
        static constexpr size_t pageSize = fse::page::size::io::constant;
        
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
        
        using SingleBranches = io::BoolWriteBuffer<Counts>;
        
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
                buffer << branchNum;
                tryFlush();
            }
            
            void onInfinite(u64 address) noexcept {
                counts.branches.infinite++;
                varintAverages.infinite << address;
                buffer << address;
                tryFlush();
            }
            
            void onInfinite(void* address) noexcept {
                // TODO lookup symbol using dladdr
                onInfinite(reinterpret_cast<u64>(address));
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
            branches.nonSingle.onInfinite(address);
        }
        
        explicit BranchCoverageRuntime() noexcept(false)
                : branches(output().dir.dir("branch")) {}
        
    };
    
    thread_local auto& rt = LazilyConstructed<BranchCoverageRuntime>::add();
    
}

namespace {
    using runtime::coverage::branch::rt;
}

#define api API_BranchCoverage

void api(onSingleBranch)(bool value) noexcept {
//    printf("BranchCoverage: onBranch: %s\n", value ? "true" : "false");
    API_rt().onSingleBranch(value);
}

void api(onMultiBranch)(u32 branchNum) noexcept {
//    printf("BranchCoverage: onMultiBranch: %d\n", branchNum);
    API_rt().onMultiBranch(branchNum);
}

void api(onSwitchCase)(bool valid, u32 caseNum) noexcept {
    if (valid) {
        __BranchCoverage_onMultiBranch(caseNum);
    }
}

void api(onInfiniteBranch)(void* address) noexcept {
//    printf("BranchCoverage: onInfiniteBranch: %p\n", address);
    API_rt().onInfiniteBranch(address);
}

void api(onFunctionStart)(void* address) noexcept {
    if (inUntracedCode) {
        inUntracedCode = false;
        __BranchCoverage_onInfiniteBranch(address);
    }
}
