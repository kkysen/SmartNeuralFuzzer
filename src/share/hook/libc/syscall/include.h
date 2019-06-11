//
// Created by Khyber on 6/5/2019.
//

#pragma once

#include <unistd.h>
#include <syscall.h>

namespace syscalls {
    
    constexpr auto raw = ::syscall;
    
}
