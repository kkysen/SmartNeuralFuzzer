//
// Created by Khyber on 6/11/2019.
//

#pragma once

#include <unistd.h>

namespace syscalls {
    
    int kill(pid_t pid, int signal) noexcept;
    
}
