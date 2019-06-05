//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/include.h"

extern "C"
int execv(const char* path, char* const argv[]) noexcept {
    trace();
    onExec();
    return impl::execv(path, argv);
}

extern "C"
int execvp(const char* file, char* const argv[]) noexcept {
    trace();
    onExec();
    return impl::execvp(file, argv);
}

extern "C"
int execvpe(const char* file, char* const argv[], char* const envp[]) noexcept {
    trace();
    onExec();
    return impl::execvpe(file, argv, envp);
}

extern "C"
int fexecve(int fd, char* const argv[], char* const envp[]) noexcept {
    trace();
    onExec();
    return impl::fexecve(fd, argv, envp);
}
