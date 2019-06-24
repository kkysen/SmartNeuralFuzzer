//
// Created by Khyber on 3/14/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_BranchCoverage(funcName) API(BranchCoverage, funcName)

#define api API_BranchCoverage

api(onSingleBranch)(bool value) noexcept;

api(onMultiBranch)(u32 branchNum, u32 numBranches) noexcept;

api(onSwitchCase)(bool valid, u32 caseNum, u32 numCases) noexcept;

api(onInfiniteBranch)(void* address) noexcept;

#undef api
