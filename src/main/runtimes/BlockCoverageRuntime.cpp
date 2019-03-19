//
// Created by Khyber on 3/14/2019.
//

#include "BlockCoverageRuntime.h"

#include <cstdio>

API_BlockCoverage(onBlock)(u32 blockNum) {
    printf("BlockCoverage: onBlock: %d\n", blockNum);
}
