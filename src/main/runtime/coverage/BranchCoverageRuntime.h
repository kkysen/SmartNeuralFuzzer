//
// Created by Khyber on 3/14/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_BranchCoverage(funcName) API(BranchCoverage, funcName)

#define api API_BranchCoverage

extern "C" {

extern const u64 api (numFunctions);

void api (onSingleBranch)(bool value) noexcept;

void api (onMultiBranch)(u64 branchNum, u64 numBranches) noexcept;

void api (onSwitchCase)(bool valid, u64 caseNum, u64 numCases) noexcept;

// address must be a pointer to a symbol, usually a function
void api (onInfiniteBranch)() noexcept;

void api (onFunction)(u64 functionIndex) noexcept;

}

#undef api
