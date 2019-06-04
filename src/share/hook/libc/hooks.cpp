//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hook/libc/hooks.h"

#include "src/share/hook/libc/impl.h"
#include "src/share/hook/lifecycle/ProcessLifeCycles.h"
#include "src/share/hook/lifecycle/signaling/signaling.h"
#include "src/share/capability/reboot.h"

#include <cassert>

namespace {
    
    using namespace hook::lifecycle;
    
    void reconstruct() {
        ProcessLifeCycles::onProcessReconstruction();
    }
    
    void destruct() noexcept {
        ProcessLifeCycles::onProcessDestruction();
    }
    
}

namespace impl = hook::libc::impl;

namespace hook::libc {
    
    void onExit() noexcept {
        destruct();
    }
    
    void onExec() noexcept {
        destruct();
    }
    
    void onKill() noexcept {
        destruct();
    }
    
    void onCrash() noexcept {
        destruct();
    }
    
    void onFork(pid_t cpid) {
        if (!cpid) {
            // if in child
            reconstruct();
        }
    }
    
    void onSignalWarning(int signal) noexcept {
        const auto* dispositionPtr = aio::signal::disposition::getDefault(signal);
        if (!dispositionPtr) {
            return;
        }
        const auto& disposition = *dispositionPtr;
        if (disposition.isUnstoppable) {
            // normally these are uncatchable (SIGKILL, SIGSTOP),
            // but I'm catching them before they're raised
            // so I have a chance to clean up first
            onKill();
        } else if (disposition.terminates) {
            // only call onCrash() if we're sure the program will exit immediately
            if (impl::signal(signal, nullptr) == SIG_DFL) {
                onKill();
            }
        }
    }
    
    void onSignalHandlerChange(int signal) noexcept {
        if (signal == lifecycle::signaling::constants::signal) {
            // TODO
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

#define trace() printf("%s\n", __func__)

using namespace hook::libc;

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


pid_t fork() noexcept {
    trace();
    const auto cpid = impl::fork();
    onFork(cpid);
    return cpid;
}

pid_t vfork() noexcept {
    trace();
    const auto cpid = impl::vfork();
    onFork(cpid); // TODO is this necessary
    return cpid;
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

// variadic functions

// https://code.woboq.org/userspace/glibc/posix/execle.c.html
#define exec_varargs() \
    std::ptrdiff_t argc; \
    va_list args = {}; \
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


int raise(int signal) noexcept {
    trace();
    onSignalWarning(signal);
    return impl::raise(signal);
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

int killpg(int processGroup, int signal) noexcept {
    if (processGroup == 0) {
        onSignalWarning(signal);
    }
    return impl::killpg(processGroup, signal);
}

int pthread_kill(pthread_t thread, int signal) noexcept {
    onSignalWarning(signal);
    return impl::pthread_kill(thread, signal);
}

int reboot(int cmd) noexcept {
    bool shouldKill = false;
    switch (static_cast<u32>(cmd)) {
        case RB_AUTOBOOT:
        case RB_HALT_SYSTEM:
        case RB_POWER_OFF:
        case RB_SW_SUSPEND:
        case RB_KEXEC: {
            if (capability::reboot()) {
                shouldKill = true;
            }
        }
    }
    if (shouldKill) {
        onKill();
    }
    const auto retVal = impl::reboot(cmd);
    if (shouldKill) {
        perror("Correct reboot() call did not work, but we already shut down some stuff");
        impl::raise(SIGKILL);
    }
    return retVal;
}

}

#undef trace
#undef impl
