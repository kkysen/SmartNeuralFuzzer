//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/hook/libc/hooks.h"
#include "src/share/hook/libc/impl.h"

namespace {
    using namespace hook::libc;
}

#include <cstdio>
#define trace() printf("%s\n", __func__)
