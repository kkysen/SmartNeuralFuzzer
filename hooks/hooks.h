//
// Created by Khyber on 2/4/2019.
//

#pragma once

#include "numbers.h"

extern "C"
void __sanitizer_cov_trace_pc_guard_init(u32* start, u32* stop);

extern "C"
void __sanitizer_cov_trace_pc_guard(u32* guard);

extern "C"
void __sanitizer_cov_trace_cmp1(u8 arg1, u8 arg2);

extern "C"
void __sanitizer_cov_trace_cmp2(u16 arg1, u16 arg2);

extern "C"
void __sanitizer_cov_trace_cmp4(u32 arg1, u32 arg2);

extern "C"
void __sanitizer_cov_trace_cmp8(u64 arg1, u64 arg2);