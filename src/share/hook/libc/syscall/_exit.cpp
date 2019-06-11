//
// Created by Khyber on 6/11/2019.
//

#include "src/share/hook/libc/syscall/_exit.h"

#include "src/share/hook/libc/syscall/include.h"

namespace syscalls {
    
    void _exit(int status) noexcept {
        raw(SYS_exit_group, status);
        for(;;);
    }
    
}
