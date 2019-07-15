//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hook/libc/impl.h"

#include "src/share/dl/Function.h"

extern "C" {
pid_t __libc_fork() noexcept;
pid_t __libc_vfork() noexcept;
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
    
    #define _(F) \
        static constexpr char name[] = ""#F; \
        return dl::Function<decltype(F), name>::impl
    
    // unconditionally hook
    // onThreadConstruction
    int pthread_create(pthread_t* thread, const pthread_attr_t* attr,
                       void* (* startRoutine)(void*), void* arg) noexcept {
        _(pthread_create)(thread, attr, startRoutine, arg);
    }
    
    // unconditionally hook
    // onExec
    int execv(const char* path, char* const argv[]) noexcept {
        _(execv)(path, argv);
    }
    
    int execvp(const char* file, char* const argv[]) noexcept {
        _(execvp)(file, argv);
    }
    
    int execvpe(const char* file, char* const argv[], char* const envp[]) noexcept {
        _(execvpe)(file, argv, envp);
    }
    
    int fexecve(int fd, char* const argv[], char* const envp[]) noexcept {
        _(fexecve)(fd, argv, envp);
    }
    
    // unconditionally hook
    // onExit

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-noreturn"
    
    void _exit(int status) noexcept {
        _(_exit)(status);
    }
    
    void _Exit(int status) noexcept {
        _(_Exit)(status);
    }
    
    void quick_exit(int status) noexcept {
        _(quick_exit)(status);
    }
    
    #pragma clang diagnostic pop
    
    // unconditionally hook
    // signal::onWarning -> onKill
    int raise(int signal) noexcept {
        _(raise)(signal);
    }
    
    // conditionally hook
    // signal::onWarning -> onKill
    int kill(pid_t pid, int signal) noexcept {
        _(kill)(pid, signal);
    }
    
    int killpg(pid_t processGroup, int signal) noexcept {
        _(killpg)(processGroup, signal);
    }
    
    int pthread_kill(pthread_t thread, int signal) noexcept {
        _(pthread_kill)(thread, signal);
    }
    
    // conditionally hook
    // onKill
    int reboot(int how) noexcept {
        _(reboot)(how);
    }
    
    // change signal handlers
    // signal::onHandlerChange
    sighandler_t signal(int signalNumber, sighandler_t handler) noexcept {
        _(signal)(signalNumber, handler);
    }
    
    int sigaction(int signal, const struct sigaction* action, struct sigaction* oldAction) noexcept {
        _(sigaction)(signal, action, oldAction);
    }
    
    // change signal mask
    // don't allow lifecycle::signaling::constants::signal
    int sigprocmask(int how, const sigset_t* mask, sigset_t* oldMask) noexcept {
        _(sigprocmask)(how, mask, oldMask);
    }
    
    int pthread_sigmask(int how, const sigset_t* mask, sigset_t* oldMask) noexcept {
        _(pthread_sigmask)(how, mask, oldMask);
    }
    
    // change signal mask or handlers
    // old APIs but still need to guard it
    sighandler_t sigset(int signal, sighandler_t disposition) noexcept {
        _(sigset)(signal, disposition);
    }
    
    int sighold(int signal) noexcept {
        _(sighold)(signal);
    }
    
}
