//
// Created by Khyber on 3/14/2019.
//

#include <cstdio>
#include "BranchCoverageRuntime.h"

API_BranchCoverage(onBranch)(bool value) {
    printf("BranchCoverage: onBranch: %s\n", value ? "true" : "false");
}

API_BranchCoverage(onMultiBranch)(u32 branchNum, u32 numBranches) {
    printf("BranchCoverage: onMultiBranch: %d/%d\n", branchNum, numBranches);
}

API_BranchCoverage(onInfiniteBranch)(u64 address) {
    printf("BranchCoverage: onInfiniteBranch: %lx\n", address);
}
