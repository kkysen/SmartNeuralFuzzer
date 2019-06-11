//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "src/share/aio/signal/mask/How.h"

namespace aio::signal::mask {
    
    class Apply {
    
    public:
        
        using Function = int (*)(int, const sigset_t*, sigset_t*) noexcept;
        
        enum Type { process, thread };
    
    private:
        
        Type type;
        
        constexpr Function raw() const noexcept {
            switch (type) {
                case process:
                    return ::sigprocmask;
                case thread:
                    return ::pthread_sigmask;
            }
        }
    
    public:
        
        /*implicit*/ constexpr Apply(Type type) noexcept : type(type) {}
        
        bool operator()(How how, const sigset_t* set, sigset_t* old) const noexcept;
        
        bool operator()(How how, const sigset_t& set, sigset_t& old) const noexcept;
        
        bool operator()(How how, const sigset_t& set) const noexcept;
        
    };
    
}
