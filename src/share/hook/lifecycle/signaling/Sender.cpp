//
// Created by Khyber on 6/3/2019.
//

#include "src/share/hook/lifecycle/signaling/Sender.h"

#include "src/share/hook/libc/syscall/sigqueueinfo.h"

namespace hook::lifecycle::signaling {
    
    void Sender::operator()(pid_t tid) {
        syscalls::rt_tgsigqueueinfo(info.rt.pid, tid, constants::signal, &info.impl());
    }
    
}
