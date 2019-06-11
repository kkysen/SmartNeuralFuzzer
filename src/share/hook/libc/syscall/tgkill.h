//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include <unistd.h>

namespace syscalls {
    
    int tgkill(pid_t tgid, pid_t tid, int signal) noexcept;
    
}
