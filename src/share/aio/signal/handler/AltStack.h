//
// Created by Khyber on 5/26/2019.
//

#pragma once

#include "src/share/common/numbers.h"

#include <array>

#include <csignal>

namespace aio::signal::handler {
    
    class AltStack {

    public:
        
        static constexpr size_t size = SIGSTKSZ;
        static_assert(size >= MINSIGSTKSZ);
        
    private:
        
        static constexpr u32 isAltStackFlag = SA_ONSTACK;
        
        using Stack = std::array<u8, size>;
        
        mutable Stack stack = {};
        bool _registered = false;
        
        bool register_(int flags) const noexcept;
        
        bool register_() const noexcept;

        struct FlagKey {};
        
    public:
        
        class Flag {

        private:
            
            const bool registered;

        public:

            // FlagKey only accessible by AltStack
            explicit constexpr Flag(bool registered, FlagKey) noexcept : registered(registered) {}
            
            constexpr u32 operator|(const u32& other) const noexcept {
                return registered ? other | isAltStackFlag : other & ~isAltStackFlag;
            }
            
        };
        
        constexpr bool registered() const noexcept {
            return _registered;
        }

        constexpr Flag flag() const noexcept {
            return Flag(registered(), FlagKey());
        }
        
        AltStack() noexcept;
        
    };
    
    constexpr u32 operator|(const u32& lhs, const AltStack::Flag& rhs) noexcept {
        return rhs | lhs;
    }
    
    constexpr u32& operator|=(u32& lhs, const AltStack::Flag& rhs) noexcept {
        return lhs = lhs | rhs;
    }
    
    constexpr i32& operator|=(i32& lhs, const AltStack::Flag& rhs) noexcept {
        return lhs = lhs | rhs;
    }
    
}
