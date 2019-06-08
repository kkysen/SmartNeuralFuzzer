//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/include.h"
#include "src/share/common/hardAssert.h"

namespace {
    
    [[noreturn]] void outdatedAPI() noexcept {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
        hardAssert(("The BSD signal API is too old. Its masks are only 32-bits, so the API doesn't work.", false)); // NOLINT(cert-dcl03-c,hicpp-static-assert,misc-static-assert)
#pragma clang diagnostic pop
    }
    
}

extern "C"
int sigvec(int, const struct sigvec*, struct sigvec*) noexcept {
    outdatedAPI();
}

extern "C"
int sigblock(int) noexcept {
    outdatedAPI();
}

extern "C"
int sigsetmask(int) noexcept {
    outdatedAPI();
}

extern "C"
int siggetmask() noexcept {
    outdatedAPI();
}
