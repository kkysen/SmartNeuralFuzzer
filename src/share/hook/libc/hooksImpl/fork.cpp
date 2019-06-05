//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/include.h"

extern "C"
pid_t fork() noexcept {
    trace();
    const auto cpid = impl::fork();
    onFork(cpid);
    return cpid;
}

extern "C"
pid_t vfork() noexcept {
    trace();
    const auto cpid = impl::vfork();
    onFork(cpid); // TODO is this necessary
    return cpid;
}
