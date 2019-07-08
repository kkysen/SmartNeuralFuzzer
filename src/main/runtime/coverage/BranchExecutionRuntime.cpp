//
// Created by Khyber on 6/24/2019.
//

#include "src/main/runtime/coverage/BranchExecutionRuntime.h"

#include "src/share/io/DeltaWriteBuffer.h"
#include "src/share/common/lazy.h"

namespace runtime::coverage::branch::execute {
    
    class BranchExecutionRuntime {
    
    private:
        
        class SingleBranches {
        
        private:
        
        public:
            
            bool next() noexcept {
                return false; // TODO
            }
            
        };
        
        class NonSingleBranches {
        
        private:
            
            u64 next() noexcept {
                return 0; // TODO
            }
            
        public:
            
            u32 nextMulti() noexcept {
                return static_cast<u32>(next());
            }
            
            void* nextInfinite() noexcept {
                return reinterpret_cast<void*>(next());
            }
            
        };
        
        struct Branches {
            
            SingleBranches single;
            NonSingleBranches nonSingle;
            
        } branches;
        
        io::DeltaWriteBuffer blockOutput;
    
    public:
        
        bool nextSingleBranch() noexcept {
            return branches.single.next();
        }
        
        u32 nextMultiBranch() noexcept {
            return branches.nonSingle.nextMulti();
        }
        
        void* nextInfiniteBranch() noexcept {
            return branches.nonSingle.nextInfinite();
        }
        
        void onEdge(u64 startBlockIndex, u64 endBlockIndex) noexcept {
            blockOutput << startBlockIndex << endBlockIndex;
        }
        
    };
    
    auto rt = LazilyConstructed<BranchExecutionRuntime>();
    
}

namespace {
    using runtime::coverage::branch::execute::rt;
}

#define api API_BranchExecution

bool api (nextSingleBranch)() noexcept {
    return rt().nextSingleBranch();
}

u32 api (nextMultiBranch)() noexcept {
    return rt().nextMultiBranch();
}

void* api(nextInfiniteBranch)() noexcept {
    return rt().nextInfiniteBranch();
}

void api (onEdge)(u64 startBlockIndex, u64 endBlockIndex) noexcept {
    //    printf("BranchExecution: onEdge: %lu, %lu\n", startBlockIndex, endBlockIndex);
    rt().onEdge(startBlockIndex, endBlockIndex);
}
