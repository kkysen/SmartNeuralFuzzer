//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hook/libc/syscall/tgkill.h"

#include "src/share/hook/libc/syscall/include.h"

namespace syscalls {
    
    int tgkill(pid_t tgid, pid_t tid, int signal) noexcept {
        return raw(SYS_tgkill, tgid, tid, signal);
    }
    
}
