//
// Created by Khyber on 5/30/2019.
//

#include "src/share/aio/signal/mask/Mask.h"

namespace aio::signal::mask {
    
    Mask::Mask(Init init) noexcept : set({}) {
        init(set);
    }
    
    Mask::Mask(Init::Type init) noexcept : Mask(Init(init)) {}
    
    Mask::Mask() noexcept : Mask(Init::empty) {}
    
    bool Mask::modify(Modify modify, int signal) noexcept {
        return modify(set, signal);
    }
    
    bool Mask::add(int signal) noexcept {
        return modify(Modify::add, signal);
    }
    
    bool Mask::remove(int signal) noexcept {
        return modify(Modify::remove, signal);
    }
    
    bool Mask::has(int signal) const noexcept {
        return ::sigismember(&set, signal) == 1;
    }
    
    Mask& Mask::operator+=(int signal) noexcept {
        add(signal);
        return *this;
    }
    
    Mask& Mask::operator-=(int signal) noexcept {
        remove(signal);
        return *this;
    }
    
    bool Mask::operator&(int signal) const noexcept {
        return has(signal);
    }
    
    bool Mask::apply(Apply apply, How how, Mask& old) const noexcept {
        return apply(how, set, old.set);
    }
    
    bool Mask::apply(Apply apply, How how) const noexcept {
        return apply(how, set);
    }
    
    Mask::Mask(Apply apply, const Mask& mask, How how) noexcept : set({}) {
        apply(how, mask.set, set);
    }
    
    bool Mask::process(How how, Mask& old) const noexcept {
        return apply(Apply::process, how, old);
    }
    
    bool Mask::thread(How how, Mask& old) const noexcept {
        return apply(Apply::thread, how, old);
    }
    
    bool Mask::process(How how) const noexcept {
        return apply(Apply::process, how);
    }
    
    bool Mask::thread(How how) const noexcept {
        return apply(Apply::thread, how);
    }
    
}
