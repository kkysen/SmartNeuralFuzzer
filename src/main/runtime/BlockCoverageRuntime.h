//
// Created by Khyber on 3/14/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_BlockCoverage(funcName) API(BlockCoverage, funcName)

API_BlockCoverage(onBlock)(u32 blockNum);
