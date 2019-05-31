//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include <csignal>

namespace aio::signal::mask {
    
    class Modify {
    
    public:
        
        using Function = int (*)(sigset_t*, int) noexcept;
        
        enum Type { add, remove };
    
    private:
        
        Type type;
        
        constexpr Function raw() const noexcept {
            switch (type) {
                case add:
                    return sigaddset;
                case remove:
                    return sigdelset;
            }
        }
    
    public:
        
        /*implicit*/ constexpr Modify(Type type) noexcept : type(type) {}
        
        bool operator()(sigset_t& set, int signal) const noexcept;
        
    };
    
}
