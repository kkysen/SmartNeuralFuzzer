//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include "src/share/hooks/libc/syscall/impl.h"

#include <csignal>

#include <stdlib.h>
#include <pthread.h>

namespace hooks::libc::impl {
    
    #define _(F) extern decltype(::F)* const F
    
    // affect signal handlers
    // onSignalHandlerChange
    _(signal);
    _(sigaction);
    
    // unconditionally hook
    // onExit
    _(_exit);
    _(_Exit);
    _(quick_exit);
    
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
    // onClone
    _(fork);
    _(vfork);
    _(pthread_create);
    // variadic args
    _(clone);
    
    // unconditionally hook
    // onSignalWarning
    _(raise);
    _(abort);
    
    // conditionally hook
    // onSignalWarning
    _(kill);
    _(killpg);
    
    // unconditionally hook
    // onSuspend
    _(sigsuspend);
    _(pause);
    
    #undef _
    
}
