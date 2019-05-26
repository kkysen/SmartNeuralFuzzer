//
// Created by Khyber on 5/25/2019.
//

#include "src/share/aio/signal/Info.h"

namespace aio::signal {
    
    const Info& Info::of(const siginfo_t& info) noexcept {
        return reinterpret_cast<const Info&>(info);
    }
    
    Info& Info::of(siginfo_t& info) noexcept {
        return reinterpret_cast<Info&>(info);
    }
    
    Info::operator const siginfo_t&() const noexcept {
        return reinterpret_cast<const siginfo_t&>(*this);
    }
    
    Info::operator siginfo_t&() noexcept {
        return reinterpret_cast<siginfo_t&>(*this);
    }
    
}
