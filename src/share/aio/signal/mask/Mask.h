//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "src/share/aio/signal/mask/Init.h"
#include "src/share/aio/signal/mask/Modify.h"
#include "src/share/aio/signal/mask/Apply.h"

namespace aio::signal::mask {
    
    class Mask {
    
    private:
        
        sigset_t set;
        
    public:
    
        explicit constexpr Mask(const sigset_t& set) noexcept : set(set) {}
        
        /*implicit*/ Mask(Init init) noexcept;
    
        /*implicit*/ Mask(Init::Type init) noexcept;
        
        Mask() noexcept;
        
        static constexpr Mask of(const sigset_t& set) noexcept {
            return Mask(set);
        }
        
        constexpr const sigset_t& impl() const noexcept {
            return set;
        }
    
        constexpr sigset_t& impl() noexcept {
            return set;
        }
        
        /*implicit*/ constexpr operator const sigset_t&() const noexcept {
            return impl();
        }
        
        /*implicit*/ constexpr operator const sigset_t&() noexcept {
            return impl();
        }
        
        bool modify(Modify modify, int signal) noexcept;
        
        bool add(int signal) noexcept;
        
        bool remove(int signal) noexcept;
        
        bool has(int signal) const noexcept;
        
        Mask& operator+=(int signal) noexcept;
        
        Mask& operator-=(int signal) noexcept;
        
        bool operator&(int signal) const noexcept;
        
        bool apply(Apply apply, How how, Mask& old) const noexcept;
        
        bool apply(Apply apply, How how) const noexcept;
        
        Mask(Apply apply, const Mask& mask, How how) noexcept;
        
        bool process(How how, Mask& old) const noexcept;
        
        bool thread(How how, Mask& old) const noexcept;
        
        bool process(How how) const noexcept;
        
        bool thread(How how) const noexcept;
        
    };
    
}
