//
// Created by Khyber on 3/14/2019.
//

#include "src/main/runtime/coverage/branch/main/BranchCoverageRuntime.h"

#include "src/main/runtime/coverage/include.h"
#include "src/share/io/BitWriteBuffer.h"

#include <numeric>
#include <iostream>

namespace {
    
    thread_local bool inUnTracedCode = false;
    
}

namespace runtime::coverage::branch {
    
    class BranchCoverageRuntime {
    
    private:
        
        io::BitWriteBuffer branches;
    
    public:
        
        void onSingleBranch(bool value) noexcept {
            branches << value;
        }
        
        void onMultiBranch(u64 branchNum, u64 numBranches) noexcept {
            branches << std::pair(branchNum, numBranches);
        }
        
        explicit BranchCoverageRuntime() noexcept(false)
                : branches(writer(output().dir, "branches")) {}
        
    };
    
    thread_local auto& rt = LazilyConstructed<BranchCoverageRuntime>::add();
    
}

namespace {
    using runtime::coverage::branch::rt;
}

#define api API_BranchCoverage

void api(onSingleBranch)(bool value) noexcept {
    API_rt().onSingleBranch(value);
}

void api(onMultiBranch)(u64 branchNum, u64 numBranches) noexcept {
    API_rt().onMultiBranch(branchNum, numBranches);
}

void api(onSwitchCase)(bool valid, u64 caseNum, u64 numCases) noexcept {
    if (valid) {
        __BranchCoverage_onMultiBranch(caseNum, numCases);
    }
}

void api(onInfiniteBranch)() noexcept {
    inUnTracedCode = true;
}

void api(onFunction)(u64 functionIndex) noexcept {
    if (inUnTracedCode) {
        inUnTracedCode = false;
        __BranchCoverage_onMultiBranch(functionIndex, __BranchCoverage_numFunctions);
    }
}
