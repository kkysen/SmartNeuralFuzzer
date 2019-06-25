//
// Created by Khyber on 3/14/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_BranchCoverage(funcName) API(BranchCoverage, funcName)

#define api API_BranchCoverage

extern "C" {

void api (onSingleBranch)(bool value) noexcept;

void api (onMultiBranch)(u32 branchNum) noexcept;

void api (onSwitchCase)(bool valid, u32 caseNum) noexcept;

void api (onInfiniteBranch)(void* address) noexcept;

}

#undef api
