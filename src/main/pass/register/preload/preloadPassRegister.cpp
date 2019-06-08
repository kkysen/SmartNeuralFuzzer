//
// Created by Khyber on 6/8/2019.
//

#include "src/share/common/hardAssert.h"

#include <string>

#include <cstdlib>

#include <unistd.h>

char* getCommand(char* linkedCommand) {
    std::string_view cmd = linkedCommand;
    const auto i = cmd.rfind('/');
    return linkedCommand + (i == std::string_view::npos ? 0 : i + 1);
}

int main(int argc, char** argv) {
    hardAssert(argc >= 1);
    constexpr char pathSeparator = ':';
    constexpr const char* ldPreload = "LD_PRELOAD";
    const char* oldLdPreload = getenv(ldPreload);
    std::string newLdPreload = BIN_PATH_PASS_REGISTER;
    if (oldLdPreload) {
        (newLdPreload += pathSeparator) += oldLdPreload;
    }
    setenv(ldPreload, newLdPreload.c_str(), true);
    
    // I got this idea from ccache.
    // Just use the current name of the program to search in path,
    // so I can just make a link to this program
    // w/ the name of whatever program I want it to wrap.
    argv[0] = getCommand(argv[0]);
    execvpe(argv[0], argv, environ);
}
