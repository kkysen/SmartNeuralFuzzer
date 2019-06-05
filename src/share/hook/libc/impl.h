//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include "src/share/hook/libc/syscall/impl.h"

#include <csignal>

#include <stdlib.h>
#include <pthread.h>
#include <sys/reboot.h>

extern "C"
int sigvec(int sig, const struct sigvec *vec, struct sigvec *ovec) noexcept __attribute_deprecated__;

namespace hook::libc::impl {
    
    #define _(F) extern decltype(::F)* const F
    
    // unconditionally hook
    // onProcessConstruction
    _(fork);
    _(vfork);
    
    // unconditionally hook
    // onThreadConstruction
    _(pthread_create);
    
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
    // signal::onWarning -> onKill
    _(raise);
    
    // conditionally hook
    // signal::onWarning -> onKill
    _(kill);
    _(killpg);
    _(pthread_kill);
    
    // conditionally hook
    // onKill
    _(reboot);
    
    // change signal handlers
    // signal::onHandlerChange
    _(signal);
    _(sigaction);
    
    // change signal mask
    // don't allow lifecycle::signaling::constants::signal
    _(sigprocmask);
    _(pthread_sigmask);
    
    // change signal mask or handlers
    // old APIs but still need to guard it
    _(sigset);
    _(sighold);
    
    // really old APIs that don't really work
    // these are just going to be completely blocked
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    _(sigvec);
    _(sigblock);
    _(sigsetmask);
    _(siggetmask);
#pragma clang diagnostic pop
    
    #undef _
    
}
