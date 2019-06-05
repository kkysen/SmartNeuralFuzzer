//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hook/libc/syscall/tgkill.h"

#include "src/share/hook/libc/hooksImpl/include.h"

int tgkill(int tgid, int tid, int sig) noexcept {
    signal::Disable disable;
    return ::syscall(SYS_tgkill, tgid, tid, sig);
}
