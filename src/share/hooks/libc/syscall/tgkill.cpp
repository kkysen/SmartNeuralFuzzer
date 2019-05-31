//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hooks/libc/syscall/tgkill.h"

#include "src/share/hooks/libc/syscall/impl.h"

int tgkill(int tgid, int tid, int sig) noexcept {
    return hooks::libc::impl::syscall(SYS_tgkill, tgid, tid, sig);
}
