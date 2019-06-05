//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/include.h"

extern "C"
int raise(int signal) noexcept {
    trace();
    onSignalWarning(signal);
    return impl::raise(signal);
}

extern "C"
int kill(pid_t pid, int signal) noexcept {
    trace();
    pid_t own;
    if (signal != 0 &&
        (pid == 0 /*|| pid == -1*/
         || (pid > 0 && pid == (own = getpid()))
         || (pid < -1 && -pid == own))) {
        onSignalWarning(signal);
    }
    return impl::kill(pid, signal);
}

extern "C"
int killpg(int processGroup, int signal) noexcept {
    trace();
    if (processGroup == 0) {
        onSignalWarning(signal);
    }
    return impl::killpg(processGroup, signal);
}

extern "C"
int pthread_kill(pthread_t thread, int signal) noexcept {
    trace();
    onSignalWarning(signal);
    return impl::pthread_kill(thread, signal);
}
