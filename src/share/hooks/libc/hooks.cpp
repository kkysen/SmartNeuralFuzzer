//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hooks/lifecycle/hooks.h"

#include "src/share/aio/signal/Handler.h"
#include "src/share/hooks/libc/impl.h"

#include <unistd.h>
#include <sys/syscall.h>

namespace {
    
    void onDeath() {
    
    }
    
}

namespace {
    
    using namespace hooks::lifecycle;
    
    void onMaybeExit() noexcept {
        flush();
    }
    
    void onExit() noexcept {
        destruct();
    }
    
    void onExec() noexcept {
        destruct();
    }
    
    void onClone() noexcept(noexcept(reconstruct)) {
        reconstruct();
    }
    
    void onSignalHandlerChange(int signal) noexcept {
        // TODO is this right
        aio::signal::Handler::get().registerFor(signal);
    }
    
    void onSignalWarning(int signal) noexcept {
        // this reduces the amount of work
        // that has to be done in the signal handler, where it's very dangerous
        const auto* dispositionPtr = aio::signal::disposition::getDefault(signal);
        if (!dispositionPtr) {
            return;
        }
        const auto& disposition = *dispositionPtr;
        if (disposition.isUnstoppable) {
            // normally these are uncatchable (SIGKILL, SIGSTOP),
            // but I'm catching them before they're raised
            // so I have a chance to clean up first
            onExit();
        } else {
            onMaybeExit();
        }
    }
    
}

namespace {
    
    template <typename R, void inside()>
    class Wrapped {
    
    public:
        
        using F = R(*)(void*);
    
    private:
        
        class Arg {
            
            const F f;
            void* const arg;
        
        public:
            
            constexpr Arg(F f, void* arg) noexcept : f(f), arg(arg) {}
            
            R operator()() {
                return f(arg);
            }
            
        };
        
        std::unique_ptr<Arg> _arg;
    
    public:
        
        F f = [](void* arg) {
            inside();
            return (*reinterpret_cast<Arg*>(arg))();
        };
        
        constexpr Wrapped(F f, void* arg) : _arg(std::make_unique<Arg>(f, arg)) {}
        
        constexpr Arg* arg() const noexcept {
            return &*_arg;
        }
        
    };
    
}

#define impl hooks::libc::impl
#define trace() printf("%s\n", __func__)

extern "C" {

sighandler_t signal(int signal, sighandler_t handler) noexcept {
//    trace();
    printf("%s(%d)\n", __func__, signal);
    const auto retVal = impl::signal(signal, handler);
    if (handler) {
        // skip nullptr handler that doesn't change anything
        onSignalHandlerChange(signal);
    }
    return retVal;
}

int sigaction(int signal, const struct sigaction* action, struct sigaction* oldAction) noexcept {
//    trace();
    printf("%s(%d)\n", __func__, signal);
    const auto retVal = impl::sigaction(signal, action, oldAction);
    if (action) {
        // skip nullptr action that doesn't change anything
        onSignalHandlerChange(signal);
    }
    return retVal;
}

void _exit(int status) {
    trace();
    onExit();
    impl::_exit(status);
}

void _Exit(int status) {
    trace();
    onExit();
    impl::_Exit(status);
}

void quick_exit(int status) {
    trace();
    onExit();
    impl::quick_exit(status);
}

int execv(const char* path, char* const argv[]) noexcept {
    trace();
    onExec();
    return impl::execv(path, argv);
}

int execvp(const char* file, char* const argv[]) noexcept {
    trace();
    onExec();
    return impl::execvp(file, argv);
}

int execvpe(const char* file, char* const argv[], char* const envp[]) noexcept {
    trace();
    onExec();
    return impl::execvpe(file, argv, envp);
}

int fexecve(int fd, char* const argv[], char* const envp[]) noexcept {
    trace();
    onExec();
    return impl::fexecve(fd, argv, envp);
}

pid_t fork() noexcept {
    trace();
    onClone();
    return impl::fork();
}

pid_t vfork() noexcept {
    trace();
    onClone(); // TODO is this necessary
    return impl::vfork();
}

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

int raise(int signal) noexcept {
    trace();
    onSignalWarning(signal);
    return impl::raise(signal);
}

void abort() noexcept {
    trace();
    onSignalWarning(SIGABRT);
    impl::abort();
}

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (* startRoutine)(void*), void* arg) {
    trace();
    Wrapped<void*, onClone> wrapped(startRoutine, arg);
    return impl::pthread_create(thread, attr, wrapped.f, wrapped.arg());
}

// variadic functions

// https://code.woboq.org/userspace/glibc/posix/execle.c.html
#define exec_varargs() \
    std::ptrdiff_t argc; \
    va_list args; \
    va_start(args, arg); \
    for (argc = 1; va_arg(args, const char*); argc++) { \
        if (argc == INT_MAX) { \
            va_end(args); \
            errno = E2BIG; \
            return -1; \
        } \
    } \
    va_end(args); \
     \
    char* argv[argc + 1]; \
    va_start(args, arg); \
    argv[0] = const_cast<char*>(arg); \
    for (std::ptrdiff_t i = 1; i <= argc; i++) { \
        argv[i] = va_arg(args, char*); \
    }

int execl(const char* path, const char* arg, ...) noexcept {
    trace();
    exec_varargs();
    va_end(args);
    
    return execv(path, argv);
}

int execlp(const char* file, const char* arg, ...) noexcept {
    trace();
    exec_varargs();
    va_end(args);
    
    return execvp(file, argv);
}

int execle(const char* path, const char* arg, ... /*, char* const envp[]*/) noexcept {
    trace();
    exec_varargs();
    char** envp = va_arg(args, char **);
    va_end(args);
    
    return execvpe(path, argv, envp);
}

int clone(int (* fn)(void*), void* child_stack, int flags, void* arg, ...
        /*, pid_t *ptid, void *newtls, pid_t *ctid */ ) {
    trace();
    Wrapped<int, onClone> wrapped(fn, arg);
    // FIXME how do I deal with variadic args
    return impl::clone(wrapped.f, child_stack, flags, wrapped.arg());
}

long syscall(long number, ...) {
    trace();
    switch (number) {
        #ifdef SYS_sigaction
        case SYS_sigaction:
        #endif
        #ifdef SYS_signal
        case SYS_signal:
        #endif
        case SYS_rt_sigaction: {
            const int signal = 0; // TODO
            onSignalHandlerChange(signal);
            break;
        }
        #ifdef SYS_clone2
            case SYS_clone2:
        #endif
        case SYS_clone:
            // TODO
            break;
        case SYS_fork:
        case SYS_vfork: {
            onClone();
            break;
        }
        #ifdef SYS_execv
            case SYS_execv:
        #endif
        case SYS_execve:
        case SYS_execveat: {
            onExec();
            break;
        }
        case SYS_exit:
        case SYS_exit_group: {
            onExit();
            break;
        }
        default:
            break;
    }
    
    // FIXME how do I deal with variadic args
    return impl::syscall(number);
}

}

#undef trace
#undef impl
