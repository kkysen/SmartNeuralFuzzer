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
        
        const std::string_view name;
        
        constexpr Default(int signal, Disposition disposition, std::string_view name) noexcept
                : signal(signal), disposition(disposition),
                  isUnstoppable(disposition == Disposition::unstoppable),
                  onlyTerminates(disposition == Disposition::terminate),
                  isUnrecoverable(disposition == Disposition::unrecoverable),
                  dumpsCore(isUnrecoverable || disposition == Disposition::coreDump),
                  terminates(onlyTerminates || dumpsCore),
                  stops(disposition == Disposition::stop),
                  atLeastStops(terminates || stops),
                  resumes(disposition == Disposition::resume),
                  isIgnored(disposition == Disposition::ignore),
                  name(name) {}
    
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
        Default(_signal, Disposition::_disposition, std::string_view(#_signal))
    
    // http://man7.org/linux/man-pages/man7/signal.7.html
    constexpr std::array<Default, 33> defaults = {
            _(SIGABRT, coreDump),
            _(SIGALRM, terminate),
            _(SIGBUS, unrecoverable),
            _(SIGCHLD, ignore),
            _(SIGCONT, resume),
//          _(SIGEMT, terminate),
            _(SIGFPE, unrecoverable),
            _(SIGHUP, terminate),
            _(SIGILL, unrecoverable),
//          _(SIGINFO, terminate),
            _(SIGINT, terminate),
            _(SIGIO, terminate),
            _(SIGIOT, coreDump),
            _(SIGKILL, unstoppable), // terminate
//          _(SIGLOST, terminate),
            _(SIGPIPE, terminate),
            _(SIGPOLL, terminate),
            _(SIGPROF, terminate),
            _(SIGPWR, terminate),
            _(SIGQUIT, coreDump),
            _(SIGSEGV, unrecoverable),
            _(SIGSTKFLT, terminate),
            _(SIGSTOP, unstoppable), // stop
            _(SIGTSTP, stop),
            _(SIGSYS, coreDump),
            _(SIGTERM, terminate),
            _(SIGTRAP, coreDump),
            _(SIGTTIN, stop),
            _(SIGTTOU, stop),
//          _(SIGUNUSED, coreDump),
            _(SIGURG, ignore),
            _(SIGUSR1, terminate),
            _(SIGUSR1, terminate),
            _(SIGVTALRM, terminate),
            _(SIGXCPU, coreDump),
            _(SIGXFSZ, coreDump),
            _(SIGWINCH, ignore),
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
