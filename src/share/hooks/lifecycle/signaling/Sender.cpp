//
// Created by Khyber on 6/3/2019.
//

#include "src/share/hooks/lifecycle/signaling/Sender.h"

#include "src/share/hooks/libc/syscall/sigqueueinfo.h"

namespace hooks::lifecycle::signaling {
    
    void Sender::operator()(pid_t tid) {
        ::rt_tgsigqueueinfo(info.rt.pid, tid, constants::signal, &info.impl());
    }
    
}
