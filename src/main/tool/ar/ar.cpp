//
// Created by Khyber on 6/12/2019.
//

#include <string>

#include <cstdlib>
#include <cerrno>

#include <unistd.h>
#include <wait.h>

namespace real {
    
    constexpr auto ar = "llvm-ar";
    constexpr auto link = "llvm-link";
    
}

[[noreturn]] void exec(const char* const* const argv) {
    execvp(argv[0], (char**) argv);
    exit(errno);
}

[[noreturn]] void archive(const char** const argv) {
    argv[0] = real::ar;
    exec(argv);
}

[[noreturn]] void link(const char** const argv) {
    argv[0] = real::link;
    argv[1] = "-o";
    std::string output = argv[2];
    const auto i = output.find_last_of('.');
    if (i != std::string::npos) {
        output.resize(i);
    }
    output += ".bc";
    argv[2] = output.c_str();
    if (unlink(argv[2]) == -1) {
        errno = 0; // don't care about errors
    }
    exec(argv);
}

int main(const int argc, const char** const argv) {
    if (argc < 1) {
        return EXIT_FAILURE;
    }
    if (argc < 3) {
        archive(argv);
    }
    switch (fork()) {
        case -1:
            return errno;
        case 0: {
            link(argv);
        }
        default: {
            break;
        }
    }
    switch (fork()) {
        case -1:
            return errno;
        case 0: {
            archive(argv);
        }
        default: {
            break;
        }
    }
    int status1;
    int status2;
    wait(&status1);
    wait(&status2);
    return WEXITSTATUS(status1) || WEXITSTATUS(status2);
}
