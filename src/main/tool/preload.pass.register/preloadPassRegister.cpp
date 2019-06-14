//
// Created by Khyber on 6/8/2019.
//

#include "src/share/io/env/LdPreload.h"
#include "src/share/common/hardAssert.h"

#include <string>
#include <iostream>

#include <cstdlib>

#include <unistd.h>

void printCommand(int argc, const char* const* argv) {
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
}

char* getCommand(char* linkedCommand) {
    std::string_view cmd = linkedCommand;
    const auto i = cmd.rfind('/');
    return linkedCommand + (i == std::string_view::npos ? 0 : i + 1);
}

int main(int argc, char** argv) {
//    printCommand(argc, argv);
    hardAssert(argc >= 1);
    
    env::path::LdPreload ldPreload;
    ldPreload.load();
    ldPreload += BIN_PATH_PASS_REGISTER;
    ldPreload.store();
    
    // I got this idea from ccache.
    // Just use the current name of the program to search in path,
    // so I can just make a link to this program
    // w/ the name of whatever program I want it to wrap.
    argv[0] = getCommand(argv[0]);
    execvpe(argv[0], argv, environ);
}
