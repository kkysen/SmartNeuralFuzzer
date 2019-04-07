//
// Created by Khyber on 3/14/2019.
//

#pragma once



#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_BranchCoverage(funcName) API(BranchCoverage, funcName)

API_BranchCoverage(onSingleBranch)(bool value) noexcept;

API_BranchCoverage(onMultiBranch)(u32 branchNum, u32 numBranches) noexcept;

API_BranchCoverage(onInfiniteBranch)(void* address) noexcept;
