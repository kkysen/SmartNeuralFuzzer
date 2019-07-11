//
// Created by Khyber on 7/11/2019.
//

#pragma once

#include <dlfcn.h>

namespace dl {
    
    template <class F, const char* name, class... Args>
    class Function {
        
        static auto lookup(Args ... args) noexcept {
            impl = (F*) dlsym(RTLD_NEXT, name);
            return impl(args...);
        }
    
    public:
        
        static F* impl;
        
    };
    
    template <class F, const char* name, class... Args>
    F* Function<F, name, Args...>::impl = lookup;
    
}
