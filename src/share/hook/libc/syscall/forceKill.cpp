//
// Created by Khyber on 6/11/2019.
//

#include "src/share/hook/libc/syscall/forceKill.h"

#include "src/share/hook/libc/syscall/kill.h"

#include <csignal>

namespace syscalls {
    
    [[noreturn]] void forceKill() {
        kill(getpid(), SIGKILL);
        for(;;);
    }
    
}
