//
// Created by Khyber on 6/11/2019.
//

#include "src/share/hook/libc/syscall/kill.h"

#include "src/share/hook/libc/syscall/include.h"

namespace syscalls {
    
    int kill(pid_t pid, int signal) noexcept {
        return raw(SYS_kill, pid, signal);
    }
    
}
