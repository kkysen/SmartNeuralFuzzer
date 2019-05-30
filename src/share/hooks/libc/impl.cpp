//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hooks/libc/impl.h"

#include <dlfcn.h>

extern "C" {
pid_t __libc_fork() noexcept;
pid_t __libc_vfork() noexcept;
}

namespace hooks::libc::impl {
    
    #define getImpl(F) ((decltype(::F)*) dlsym(RTLD_NEXT, ""#F))
    #define _(F) const auto F = getImpl(F)
    
    _(signal);
    _(sigaction);
    _(_exit);
    _(_Exit);
    _(quick_exit);
    _(execv);
    _(execvp);
    _(execvpe);
    _(fexecve);
    
    const auto fork = __libc_fork;
    const auto vfork = __libc_vfork;
    
    _(kill);
    _(raise);
    _(abort);
    _(pthread_create);
    
    _(execl);
    _(execlp);
    _(execle);
    _(clone);
    _(syscall);
    
    #undef _
    #undef getImpl
    
}
