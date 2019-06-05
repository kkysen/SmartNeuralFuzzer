//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include <cstdint>
#include <csignal>

namespace aio::signal::handler {
    
    class Const {
    
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
        
        /*implicit*/ constexpr Const(Raw raw) noexcept : raw(raw) {}
        
        /*implicit*/ constexpr operator Raw() noexcept {
            return raw;
        }
        
        /*implicit*/ Const(sighandler_t handler) noexcept;
        
        /*implicit*/ operator sighandler_t() noexcept;
        
        constexpr bool operator==(const Raw& rhs) const noexcept {
            return raw == rhs;
        }
        
    };
    
    constexpr bool operator==(const typename Const::Raw& lhs, const Const& rhs) noexcept {
        return rhs == lhs;
    }
    
    constexpr bool operator!=(const Const& lhs, const typename Const::Raw& rhs) noexcept {
        return !(lhs == rhs);
    }
    
    constexpr bool operator!=(const typename Const::Raw& lhs, const Const& rhs) noexcept {
        return !(lhs == rhs);
    }
    
}
