//
// Created by Khyber on 6/3/2019.
//

#include "src/share/hook/libc/syscall/sigqueueinfo.h"

#include "src/share/hook/libc/syscall/include.h"

namespace syscalls {
    
    int rt_sigqueueinfo(pid_t tgid, int signal, siginfo_t* info) noexcept {
        return raw(SYS_rt_sigqueueinfo, tgid, signal, info);
    }
    
    int rt_tgsigqueueinfo(pid_t tgid, pid_t tid, int signal, siginfo_t* info) noexcept {
        return raw(SYS_rt_tgsigqueueinfo, tgid, tid, signal, info);
    }
    
}