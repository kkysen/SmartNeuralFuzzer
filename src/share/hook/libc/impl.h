//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include "src/share/hook/libc/syscall/impl.h"

#include <csignal>

#include <stdlib.h>
#include <pthread.h>
#include <sys/reboot.h>

namespace hook::libc::impl {
    
    #define _(F) extern decltype(::F)* const F
    
    // affect signal handlers
    // onSignalHandlerChange
    _(signal);
    _(sigaction);
    
    // unconditionally hook
    // onFork
    _(fork);
    _(vfork);
    
    // unconditionally hook
    // onExec
    _(execv);
    _(execvp);
    _(execvpe);
    _(fexecve);
    // variadic args
    _(execl);
    _(execlp);
    _(execle);
    
    // unconditionally hook
    // onExit
    _(_exit);
    _(_Exit);
    _(quick_exit);
    
    // unconditionally hook
    // onSignalWarning -> onKill
    _(raise);
    
    // conditionally hook
    // onSignalWarning -> onKill
    _(kill);
    _(killpg);
    _(pthread_kill);
    
    // conditionally hook
    // onKill
    _(reboot);
    
    #undef _
    
}
