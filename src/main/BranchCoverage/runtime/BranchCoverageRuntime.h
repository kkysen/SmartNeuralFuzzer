//
// Created by Khyber on 3/14/2019.
//

#pragma once



#include "src/share/common/numbers.h"
#include "src/share/llvm/api.h"

#define API_BranchCoverage(funcName) API(BranchCoverage, funcName)

API_BranchCoverage(onBranch)(bool value);

API_BranchCoverage(onMultiBranch)(u32 branchNum, u32 numBranches);

API_BranchCoverage(onInfiniteBranch)(u64 address);
