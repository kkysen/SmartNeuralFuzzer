//
// Created by Khyber on 3/14/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/api.h"

#define API_BlockCoverage(funcName) API(BlockCoverage, funcName)

#define api API_BlockCoverage

/*
 * I decided to use u64s here because the number of basic blocks could require such large integer IDs.
 * For most small programs, the number of basic blocks is much lower, so a smaller integer size would work.
 * This would save a lot of space for those program's outputs, and reduce IO writes.
 *
 * To solve this, I could count the number of basic blocks at compile time,
 * and then emit all the calls to onBlock() based on the minimum integer size.
 * I would then need to template the BlockCoverageRuntime on the block num size,
 * and then implement an API for each of the integer sizes.
 *
 * The other option is to use varint encoding.
 * This will dramatically reduce the size for when the number of blocks is small,
 * but will incur unnecessary overhead when the number of blocks is large.
 *
 * Another option is to use varint delta encoding.
 * If sequential basic blocks tend to be close in number, then this will produce a small delta for each one,
 * and then varint encoding will work much better and more consistently.
 *
 * Another option is to just compress the output afterwards, separate from the program.
 */

api(onFunction)(u64 functionIndex) noexcept;

api(onBlock)(u64 blockIndex) noexcept;

#undef api
