//
// Created by Khyber on 6/24/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_BranchExecution(funcName) API(BranchExecution, funcName)

#define api API_BranchExecution

extern "C" {

extern const u64 api (numFunctions);

extern const void* const* const api(functionTable);

bool api (nextSingleBranch)() noexcept;

u64 api (nextMultiBranch)(u64 numBranches) noexcept;

const void* api(nextInfiniteBranch)() noexcept;

void api (onEdge)(u64 startBlockIndex, u64 endBlockIndex) noexcept;

//void api(onEdge)(u64 edgeIndex) noexcept;

}

#undef api
