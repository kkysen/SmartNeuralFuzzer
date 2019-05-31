//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include <csignal>

namespace aio::signal::mask {
    
    class Init {
    
    public:
        
        using Function = int (*)(sigset_t*) noexcept;
        
        enum Type { empty, full };
    
    private:
        
        Type type;
        
        constexpr Function raw() const noexcept {
            switch (type) {
                case empty:
                    return ::sigemptyset;
                case full:
                    return ::sigfillset;
            }
        }
    
    public:
        
        /*implicit*/ constexpr Init(Type type) noexcept : type(type) {}
        
        void operator()(sigset_t& set) const noexcept;
        
    };
    
}
