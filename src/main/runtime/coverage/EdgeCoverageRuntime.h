//
// Created by Khyber on 3/14/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_EdgeCoverage(funcName) API(EdgeCoverage, funcName)

#define api API_EdgeCoverage

extern "C" {

void api (onFrontEdge)(u64 blockIndex) noexcept;

void api (onBackEdge)(u64 blockIndex) noexcept;

}

#undef api
