//
// Created by Khyber on 6/24/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_BranchExecution(funcName) API(BranchExecution, funcName)

#define api API_BranchExecution

extern "C" {

bool api (nextSingleBranch)() noexcept;

u32 api (nextMultiBranch)() noexcept;

void* api(nextInfiniteBranch)() noexcept;

void api(onEdge)(u64 startBlockIndex, u64 endBlockIndex) noexcept;

//void api(onEdge)(u64 edgeIndex) noexcept;

}

#undef api
