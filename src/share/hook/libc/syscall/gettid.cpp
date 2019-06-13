//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hook/libc/syscall/gettid.h"

#include "src/share/hook/libc/syscall/include.h"

namespace syscalls {
    
    // very new in glibc 2.30, 8/2019
    // skip syscall hook, like it will in glibc
    // no reason to hook it either
    pid_t gettid() noexcept {
        return raw(SYS_gettid);
    }
    
}
