//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hook/libc/impl.h"

#include <dlfcn.h>

#include <cstdio> // TODO remove

extern "C" {
pid_t __libc_fork() noexcept;
pid_t __libc_vfork() noexcept;
}

namespace {
    
    template <class F>
    F* lookup(const char* name) noexcept {
        printf("dlsym(RTLD_NEXT, %s)\n", name);
        return (F*) dlsym(RTLD_NEXT, name);
    }
    
}

namespace hook::libc::impl {
    
    // unconditionally hook
    // onProcessConstruction
    pid_t fork() noexcept {
        return __libc_fork();
    }
    
    pid_t vfork() noexcept {
        return __libc_vfork();
    }
    
    #define getImpl(F) lookup<decltype(::F)>(""#F)
    #define _(F) static const auto impl = getImpl(F)
    
    // unconditionally hook
    // onThreadConstruction
    int pthread_create(pthread_t* thread, const pthread_attr_t* attr,
                       void* (* startRoutine)(void*), void* arg) noexcept {
        _(pthread_create);
        return impl(thread, attr, startRoutine, arg);
    }
    
    // unconditionally hook
    // onExec
    int execv(const char* path, char* const argv[]) noexcept {
        _(execv);
        return impl(path, argv);
    }
    
    int execvp(const char* file, char* const argv[]) noexcept {
        _(execvp);
        return impl(file, argv);
    }
    
    int execvpe(const char* file, char* const argv[], char* const envp[]) noexcept {
        _(execvpe);
        return impl(file, argv, envp);
    }
    
    int fexecve(int fd, char *const argv[], char *const envp[]) noexcept {
        _(fexecve);
        return impl(fd, argv, envp);
    }
    
    // unconditionally hook
    // onExit
    void _exit(int status) noexcept {
        _(_exit);
        impl(status);
    }
    
    void _Exit(int status) noexcept {
        _(_Exit);
        impl(status);
    }
    
    void quick_exit(int status) noexcept {
        _(quick_exit);
        impl(status);
    }
    
    // unconditionally hook
    // signal::onWarning -> onKill
    int raise(int signal) noexcept {
        _(raise);
        return impl(signal);
    }
    
    // conditionally hook
    // signal::onWarning -> onKill
    int kill(pid_t pid, int signal) noexcept {
        _(kill);
        return impl(pid, signal);
    }
    
    int killpg(pid_t processGroup, int signal) noexcept {
        _(killpg);
        return impl(processGroup, signal);
    }
    
    int pthread_kill(pthread_t thread, int signal) noexcept {
        _(pthread_kill);
        return impl(thread, signal);
    }
    
    // conditionally hook
    // onKill
    int reboot(int how) noexcept {
        _(reboot);
        return impl(how);
    }
    
    // change signal handlers
    // signal::onHandlerChange
    sighandler_t signal(int signal, sighandler_t handler) noexcept {
        _(signal);
        return impl(signal, handler);
    }
    
    int sigaction(int signal, const struct sigaction* action, struct sigaction* oldAction) noexcept {
        _(sigaction);
        return impl(signal, action, oldAction);
    }
    
    // change signal mask
    // don't allow lifecycle::signaling::constants::signal
    int sigprocmask(int how, const sigset_t* mask, sigset_t* oldMask) noexcept {
        _(sigprocmask);
        return impl(how, mask, oldMask);
    }
    
    int pthread_sigmask(int how, const sigset_t* mask, sigset_t* oldMask) noexcept {
        _(pthread_sigmask);
        return impl(how, mask, oldMask);
    }
    
    // change signal mask or handlers
    // old APIs but still need to guard it
    sighandler_t sigset(int signal, sighandler_t disposition) noexcept {
        _(sigset);
        return impl(signal, disposition);
    }
    
    int sighold(int signal) noexcept {
        _(sighold);
        return impl(signal);
    }
    
}