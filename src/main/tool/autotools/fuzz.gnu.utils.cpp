//
// Created by Khyber on 6/17/2019.
//

#include <cstdlib>
#include <cstring>

#include <unistd.h>

const char* getName(const char* const* argv) noexcept {
    const char* const arg = argv[0];
    if (!arg) {
        return "";
    }
    const char* const dot = strrchr(arg, '.');
    if (!dot) {
        return "";
    }
    return dot + 1;
}

int main(int, char* const* argv) {
    #define buildDir BUILD_PATH
    #define srcDir BIN_PATH_FUZZ_AUTOTOOLS_DIR
    #define _(var) setenv("__"#var, var, true)
    const auto name = getName(argv);
    _(buildDir);
    _(name);
    return execve(srcDir "/fuzz.gnu.utils.sh", argv, environ);
}
