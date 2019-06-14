//
// Created by Khyber on 6/12/2019.
//

#include <cstdlib>

#include <unistd.h>

namespace {

    constexpr auto originalLDFlagsCache = "originalLDFlags.txt";
    
    constexpr auto flto = "-flto -fuse-ld=lld"; // flto makes .o files .bc files
    constexpr auto myLDFlags = flto "-Wl,-plugin-opt=save-temps" // generates .bc files also
    
    
    local myLDFLAGS="${flto} -Wl,-plugin-opt=save-temps" # generates .bc files also
            
            local cc=clang
    local cxx=clang++
    local ranlib=llvm-ranlib
    local cFlags=" -flto ${CFLAGS} "
    local ldFlags=" ${myLDFLAGS} ${LDFLAGS} "
    
    constexpr auto cc = "clang";
    constexpr auto cxx = "clang++";
    
}

int main(int, char* const* const argv) {
    setenv("__buildDir", BUILD_PATH, true);
    setenv("__srcDir", BIN_PATH_FUZZ_AUTOTOOLS_SH, true);
    execve(BIN_PATH_FUZZ_AUTOTOOLS_SH "/fuzz.autotools.sh", argv, environ);
}
