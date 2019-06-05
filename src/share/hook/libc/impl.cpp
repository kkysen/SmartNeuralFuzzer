//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hook/libc/impl.h"

#include <dlfcn.h>

extern "C" {
pid_t __libc_fork() noexcept;
pid_t __libc_vfork() noexcept;
}

namespace hook::libc::impl {
    
    #define getImpl(F) ((decltype(::F)*) dlsym(RTLD_NEXT, ""#F))
    #define _(F) const auto F = getImpl(F)
    
    const auto fork = __libc_fork;
    const auto vfork = __libc_vfork;
    
    _(execv);
    _(execvp);
    _(execvpe);
    _(fexecve);
    _(execl);
    _(execlp);
    _(execle);
    
    _(_exit);
    _(_Exit);
    _(quick_exit);
    
    _(raise);
    _(killpg);
    _(kill);
    _(pthread_kill);
    _(reboot);
    
    _(signal);
    _(sigaction);
    
    _(sigprocmask);
    _(pthread_sigmask);
    
    _(sigset);
    _(sighold);
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    _(sigvec);
    _(sigblock);
    _(sigsetmask);
    _(siggetmask);
#pragma clang diagnostic pop
    
    #undef _
    #undef getImpl
    
}
