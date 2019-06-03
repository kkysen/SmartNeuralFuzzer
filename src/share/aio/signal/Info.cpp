//
// Created by Khyber on 5/25/2019.
//

#include "src/share/aio/signal/Info.h"

#include <unistd.h>

namespace aio::signal {
    
    const Info& Info::of(const siginfo_t& info) noexcept {
        return reinterpret_cast<const Info&>(info);
    }
    
    Info& Info::of(siginfo_t& info) noexcept {
        return reinterpret_cast<Info&>(info);
    }
    
    const siginfo_t& Info::impl() const noexcept {
        return reinterpret_cast<const siginfo_t&>(*this);
    }
    
    siginfo_t& Info::impl() noexcept {
        return reinterpret_cast<siginfo_t&>(*this);
    }
    
    Info::operator const siginfo_t&() const noexcept {
        return impl();
    }
    
    Info::operator siginfo_t&() noexcept {
        return impl();
    }
    
    Info Info::value(int code, const Value& value) noexcept {
        return {
                .code = code,
                .rt = {
                        .pid = getpid(),
                        .uid = getuid(),
                        .value = value,
                },
        };
    }
    
}
