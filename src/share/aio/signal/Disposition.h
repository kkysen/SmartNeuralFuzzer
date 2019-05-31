//
// Created by Khyber on 5/25/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/common/deleteCopy.h"

#include <array>

#include <csignal>

namespace aio::signal::disposition {
    
    enum class Disposition {
        terminate,
        ignore,
        coreDump,
        stop,
        resume,
        unstoppable,
        unrecoverable,
    };
    
    struct Default {
        
        const int signal;
        const Disposition disposition;
        
        const bool isUnstoppable;
        const bool onlyTerminates;
        const bool isUnrecoverable;
        const bool dumpsCore;
        const bool terminates; // onlyTerminates or dumpsCore
        const bool stops;
        const bool atLeastStops; // includes terminates
        const bool resumes;
        const bool isIgnored;
        
        constexpr Default(int signal, Disposition disposition) noexcept
                : signal(signal), disposition(disposition),
                  isUnstoppable(disposition == Disposition::unstoppable),
                  onlyTerminates(disposition == Disposition::terminate),
                  isUnrecoverable(disposition == Disposition::unrecoverable),
                  dumpsCore(isUnrecoverable || disposition == Disposition::coreDump),
                  terminates(onlyTerminates || dumpsCore),
                  stops(disposition == Disposition::stop),
                  atLeastStops(terminates || stops),
                  resumes(disposition == Disposition::resume),
                  isIgnored(disposition == Disposition::ignore) {}
    
        deleteCopy(Default);
        
    };
    
}

namespace {
    
    #define _constexpr inline __attribute__((always_inline)) constexpr
    
    template <size_t N>
    class Indices {
    
    private:
        
        template <class F, size_t... Indices>
        static _constexpr auto mapIndex(std::index_sequence<Indices...>, F f) noexcept
        -> std::array<decltype(f(0LU)), N> {
            return {{f(Indices)...}};
        }
        
        static constexpr auto indices = std::make_index_sequence<N>();
    
    public:
        
        template <class F>
        static _constexpr auto map(F f) noexcept {
            return mapIndex(indices, f);
        }
        
    };
    
    #undef _constexpr
    
}

namespace aio::signal::disposition {
    
    #define _(_signal, _disposition) \
        Default(SIG##_signal, Disposition::_disposition)
    
    // http://man7.org/linux/man-pages/man7/signal.7.html
    constexpr std::array<Default, 34> defaults = {
            _(ABRT, coreDump),
            _(ALRM, terminate),
            _(BUS, unrecoverable),
            _(CHLD, ignore),
            _(CLD, ignore),
            _(CONT, resume),
//          _(EMT, terminate),
            _(FPE, unrecoverable),
            _(HUP, terminate),
            _(ILL, unrecoverable),
//          _(INFO, terminate),
            _(INT, terminate),
            _(IO, terminate),
            _(IOT, coreDump),
            _(KILL, unstoppable), // terminate
//          _(LOST, terminate),
            _(PIPE, terminate),
            _(POLL, terminate),
            _(PROF, terminate),
            _(PWR, terminate),
            _(QUIT, coreDump),
            _(SEGV, unrecoverable),
            _(STKFLT, terminate),
            _(STOP, unstoppable), // stop
            _(TSTP, stop),
            _(SYS, coreDump),
            _(TERM, terminate),
            _(TRAP, coreDump),
            _(TTIN, stop),
            _(TTOU, stop),
//          _(UNUSED, coreDump),
            _(URG, ignore),
            _(USR1, terminate),
            _(USR1, terminate),
            _(VTALRM, terminate),
            _(XCPU, coreDump),
            _(XFSZ, coreDump),
            _(WINCH, ignore),
    };
    
    #undef _
    
}

namespace {
    
    using namespace aio::signal::disposition;
    
    constexpr auto table = Indices<_NSIG>::map([](auto i) -> const Default* {
        const int signal = i;
        for (const auto& disposition : defaults) {
            if (disposition.signal == signal) {
                return &disposition;
            }
        }
        return nullptr;
    });
    
}

namespace aio::signal::disposition {
    
    constexpr const Default* getDefault(int signal) noexcept {
        if (signal <= 0 || static_cast<size_t>(signal) >= table.size()) {
            return nullptr;
        }
        return table[signal];
    }
    
}

namespace aio::signal {
    
    constexpr bool exists(int signal) noexcept {
        return disposition::getDefault(signal) != nullptr;
    }
    
}
