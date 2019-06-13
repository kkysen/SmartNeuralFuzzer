//
// Created by Khyber on 6/12/2019.
//

#include <string>
#include <array>

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
    
    using Run = void (*)(const char** const);
    constexpr std::array<Run, 2> programs = {link, archive};
    std::array<int, programs.size()> statuses = {};
    #define forEach() for (size_t i = 0; i < programs.size(); i++)
    forEach() {
        switch (fork()) {
            case -1: {
                statuses[i] = errno;
                break;
            }
            case 0: programs[i](argv);
            default: break;
        }
    }
    forEach() {
        if (statuses[i] == 0) {
            wait(&statuses[i]);
        }
    }
    forEach() {
        if (statuses[i]) {
            return statuses[i];
        }
    }
    #undef forEach
}
