//
// Created by Khyber on 5/24/2019.
//

#include "Signal.h"

namespace aio {
    
    const Signal::Info& Signal::Info::of(const siginfo_t& info) noexcept {
        return reinterpret_cast<const Info&>(info);
    }
    
    Signal::Info& Signal::Info::of(siginfo_t& info) noexcept {
        return reinterpret_cast<Info&>(info);
    }
    
    Signal::Info::operator const siginfo_t&() const noexcept {
        return reinterpret_cast<const siginfo_t&>(*this);
    }
    
    Signal::Info::operator siginfo_t&() noexcept {
        return reinterpret_cast<siginfo_t&>(*this);
    }
    
    Signal::Signal(int signal, const siginfo_t* sigInfo, const void* context) noexcept :
            Signal(signal, Info::of(*sigInfo), *static_cast<const ucontext_t*>(context)) {}
            
}
