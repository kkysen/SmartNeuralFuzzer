//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include <cstdlib>
#include <csignal>

#include <unistd.h>
#include <pthread.h>
#include <sys/reboot.h>

namespace hook::libc::impl {
    
    // unconditionally hook
    // onProcessConstruction
    pid_t fork() noexcept;
    
    pid_t vfork() noexcept;
    
    // unconditionally hook
    // onThreadConstruction
    int
    pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (* startRoutine)(void*), void* arg) noexcept;
    
    // unconditionally hook
    // onExec
    int execv(const char* path, char* const argv[]) noexcept;
    
    int execvp(const char* file, char* const argv[]) noexcept;
    
    int execvpe(const char* file, char* const argv[], char* const envp[]) noexcept;
    
    int fexecve(int fd, char *const argv[], char *const envp[]) noexcept;
    
    // variadic args
    // these are uncallable; the non-variadic ones are called
//    int execl(const char* path, const char* arg, ...) noexcept;
//    int execlp(const char* file, const char* arg, ...) noexcept;
//    int execle(const char* path, const char* arg, ...) noexcept;
    
    // unconditionally hook
    // onExit
    [[noreturn]] void _exit(int status) noexcept;
    
    [[noreturn]] void _Exit(int status) noexcept;
    
    [[noreturn]] void quick_exit(int status) noexcept;
    
    // unconditionally hook
    // signal::onWarning -> onKill
    int raise(int signal) noexcept;
    
    // conditionally hook
    // signal::onWarning -> onKill
    int kill(pid_t pid, int signal) noexcept;
    
    int killpg(pid_t processGroup, int signal) noexcept;
    
    int pthread_kill(pthread_t thread, int signal) noexcept;
    
    // conditionally hook
    // onKill
    int reboot(int how) noexcept;
    
    // change signal handlers
    // signal::onHandlerChange
    sighandler_t signal(int signal, sighandler_t handler) noexcept;
    
    int sigaction(int signal, const struct sigaction* action, struct sigaction* oldAction) noexcept;
    
    // change signal mask
    // don't allow lifecycle::signaling::constants::signal
    int sigprocmask(int how, const sigset_t* mask, sigset_t* oldMask) noexcept;
    
    int pthread_sigmask(int how, const sigset_t* mask, sigset_t* oldMask) noexcept;
    
    // change signal mask or handlers
    // old APIs but still need to guard it
    sighandler_t sigset(int signal, sighandler_t disposition) noexcept;
    
    int sighold(int signal) noexcept;
    
    // really old APIs that don't really work
    // these are just going to be completely blocked
//    int sigvec(int signal, const struct sigvec* vec, struct sigvec* oldVec) noexcept __attribute_deprecated__;
//    int sigblock(int mask) noexcept __attribute_deprecated__;
//    int sigsetmask(int mask) noexcept __attribute_deprecated__;
//    int siggetmask() noexcept __attribute_deprecated__;
    
}
