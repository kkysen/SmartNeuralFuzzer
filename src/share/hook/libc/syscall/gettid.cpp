//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hook/libc/syscall/gettid.h"

#include "src/share/hook/libc/hooksImpl/include.h"

// very new in glibc 2.30, 8/2019
pid_t gettid() noexcept {
    // skip syscall hook, like it will in glibc
    // no reason to hook it either
    signal::Disable disable;
    return ::syscall(SYS_gettid);
}
