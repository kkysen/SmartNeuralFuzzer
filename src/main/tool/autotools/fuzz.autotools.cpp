//
// Created by Khyber on 6/12/2019.
//

#include <cstdlib>

#include <unistd.h>

int main(int, char* const* const argv) {
    #define buildDir BUILD_PATH
    #define srcDir BIN_PATH_FUZZ_AUTOTOOLS_DIR
    #define libraries RUNTIME_COVERAGE_LIBRARIES
    #define _(var) setenv("__"#var, var, true)
    _(buildDir);
    _(srcDir);
    _(libraries);
    execve(srcDir "/fuzz.autotools.sh", argv, environ);
}
