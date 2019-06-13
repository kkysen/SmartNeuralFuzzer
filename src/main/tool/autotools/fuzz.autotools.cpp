//
// Created by Khyber on 6/12/2019.
//

#include <cstdlib>

#include <unistd.h>

int main(int, char* const* const argv) {
    setenv("__buildDir", BUILD_PATH, true);
    setenv("__srcDir", BIN_PATH_FUZZ_AUTOTOOLS_SH, true);
    execve(BIN_PATH_FUZZ_AUTOTOOLS_SH "/fuzz.autotools.sh", argv, environ);
}
