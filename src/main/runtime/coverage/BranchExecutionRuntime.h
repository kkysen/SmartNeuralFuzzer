//
// Created by Khyber on 6/24/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_BranchExecution(funcName) API(BranchExecution, funcName)

#define api API_BranchExecution

namespace runtime::coverage::branch::execute {
    
    using Func = void();
    
}

extern "C" {

extern const u64 api (numFunctions);

extern runtime::coverage::branch::execute::Func* const* const api(functionTable);

bool api (nextSingleBranch)() noexcept;

u64 api (nextMultiBranch)(u64 numBranches) noexcept;

runtime::coverage::branch::execute::Func* api(nextInfiniteBranch)() noexcept;

void api (onEdge)(u64 startBlockIndex, u64 endBlockIndex) noexcept;

//void api(onEdge)(u64 edgeIndex) noexcept;

}

#undef api
