//
// Created by Khyber on 6/12/2019.
//

#include "src/share/hook/libc/syscall/getpid.h"

#include "src/share/hook/libc/syscall/include.h"

namespace syscalls {
    
    uid_t getuid() noexcept {
        return raw(SYS_getuid);
    }
    
}
