//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hook/libc/syscall/impl.h"

#include <dlfcn.h>

namespace hook::libc::impl {
    
    #define getImpl(F) ((decltype(::F)*) dlsym(RTLD_NEXT, ""#F))
    #define _(F) const auto F = getImpl(F)
    
    _(syscall);
    
    #undef _
    #undef getImpl
    
}
