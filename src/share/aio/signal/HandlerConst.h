//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include <cstdint>
#include <csignal>

namespace aio::signal {
    
    class HandlerConst {

    public:
        
        enum Raw : intptr_t {
            error = -1, // SIG_ERR
            default_ = 0, // SIG_DFL
            ignore = 1, // SIG_IGN
            hold = 2, // SIG_HOLD
        };
    
    private:
        
        Raw raw;
        
        static bool check() noexcept;
        
        static const bool checked;
    
    public:
        
        /*implicit*/ constexpr HandlerConst(Raw raw) noexcept : raw(raw) {}
        
        /*implicit*/ constexpr operator Raw() noexcept {
            return raw;
        }
        
        /*implicit*/ HandlerConst(sighandler_t handler) noexcept;
        
        /*implicit*/ operator sighandler_t() noexcept;
        
    };
    
}
