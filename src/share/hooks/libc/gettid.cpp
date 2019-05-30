//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hooks/libc/gettid.h"
#include "src/share/hooks/libc/impl.h"

#include <syscall.h>

// very new in glibc 2.30, 8/2019
pid_t gettid() noexcept {
    // skip syscall hook, like it will in glibc
    // no reason to hook it either
    return hooks::libc::impl::syscall(SYS_gettid);
}
