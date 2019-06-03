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
        
        explicit constexpr Mask(const sigset_t& set) noexcept : set(set) {}
    
    public:
        
        /*implicit*/ Mask(Init init = Init::empty) noexcept : set({}) {
            init(set);
        }
    
        /*implicit*/ Mask(Init::Type init = Init::empty) noexcept : Mask(Init(init)) {}
        
        static constexpr Mask of(const sigset_t& set) noexcept {
            return Mask(set);
        }
        
        /*implicit*/ constexpr operator const sigset_t&() const noexcept {
            return set;
        }
        
        /*implicit*/ constexpr operator const sigset_t&() noexcept {
            return set;
        }
        
        bool modify(Modify modify, int signal) noexcept {
            return modify(set, signal);
        }
        
        bool add(int signal) noexcept {
            return modify(Modify::add, signal);
        }
        
        bool remove(int signal) noexcept {
            return modify(Modify::remove, signal);
        }
        
        bool has(int signal) const noexcept {
            return ::sigismember(&set, signal) == 1;
        }
        
        Mask& operator+=(int signal) noexcept {
            add(signal);
            return *this;
        }
        
        Mask& operator-=(int signal) noexcept {
            remove(signal);
            return *this;
        }
        
        bool operator&(int signal) noexcept {
            return has(signal);
        }
        
        bool apply(Apply apply, How how, Mask& old) const noexcept {
            return apply(how, set, old.set);
        }
        
        bool apply(Apply apply, How how) const noexcept {
            return apply(how, set);
        }
        
        Mask(Apply apply, const Mask& mask, How how) noexcept : set({}) {
            apply(how, mask.set, set);
        }
        
        bool process(How how, Mask& old) const noexcept {
            return apply(Apply::process, how, old);
        }
        
        bool thread(How how, Mask& old) const noexcept {
            return apply(Apply::thread, how, old);
        }
        
        bool process(How how) const noexcept {
            return apply(Apply::process, how);
        }
        
        bool thread(How how) const noexcept {
            return apply(Apply::thread, how);
        }
        
    };
    
}
