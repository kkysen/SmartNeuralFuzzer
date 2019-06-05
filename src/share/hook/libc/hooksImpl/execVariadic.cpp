//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/include.h"

#include <climits>
#include <cerrno>

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

extern "C"
int execl(const char* path, const char* arg, ...) noexcept {
    trace();
    exec_varargs();
    va_end(args);
    
    return execv(path, argv);
}

extern "C"
int execlp(const char* file, const char* arg, ...) noexcept {
    trace();
    exec_varargs();
    va_end(args);
    
    return execvp(file, argv);
}

extern "C"
int execle(const char* path, const char* arg, ... /*, char* const envp[]*/) noexcept {
    trace();
    exec_varargs();
    char** envp = va_arg(args, char **);
    va_end(args);
    
    return execvpe(path, argv, envp);
}

#undef exec_varargs
