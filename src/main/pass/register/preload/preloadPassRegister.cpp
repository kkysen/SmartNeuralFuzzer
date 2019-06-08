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
    argv[0] = getCommand(argv[0]);
    execvpe(argv[0], argv, environ);
}
