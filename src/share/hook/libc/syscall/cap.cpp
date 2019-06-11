//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/syscall/cap.h"

#include "src/share/hook/libc/syscall/include.h"

namespace syscalls {
    
    int capget(__user_cap_header_struct* header, __user_cap_data_struct* data) noexcept {
        return raw(SYS_capget, header, data);
    }
    
    int capset(__user_cap_header_struct* header, const __user_cap_data_struct* data) noexcept {
        return raw(SYS_capset, header, data);
    }
    
}
