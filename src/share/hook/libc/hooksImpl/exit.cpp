//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/include.h"

extern "C"
void _exit(int status) {
    trace();
    onExit();
    impl::_exit(status);
}

extern "C"
void _Exit(int status) {
    trace();
    onExit();
    ::impl::_Exit(status);
}

extern "C"
void quick_exit(int status) {
    trace();
    onExit();
    ::impl::quick_exit(status);
}
