//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include <unistd.h>
#include <syscall.h>

namespace hook::libc::impl {
    
    #define _(F) extern decltype(::F)* const F
    
    _(syscall);
    
    #undef _
    
}
