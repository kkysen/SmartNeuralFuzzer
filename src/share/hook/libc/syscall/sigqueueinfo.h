//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include <csignal>

namespace syscalls {
    
    int rt_sigqueueinfo(pid_t tgid, int signal, siginfo_t* info) noexcept;
    
    int rt_tgsigqueueinfo(pid_t tgid, pid_t tid, int signal, siginfo_t* info) noexcept;
    
}
