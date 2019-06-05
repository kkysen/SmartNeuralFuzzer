//
// Created by Khyber on 5/25/2019.
//

#pragma once

#include "src/share/aio/signal/handler/Raw.h"
#include "src/share/aio/signal/Signal.h"
#include "src/share/aio/signal/handler/Flag.h"
#include "src/share/aio/signal/handler/Const.h"

namespace aio::signal::handler {
    
    // like sigaction, but no sigset_t mask, which is large
    // doesn't support SIG_DFL either, i.e., when executing, SIG_DFL is treated as SIG_IGN
    // also doesn't store sa_restorer, but that's never used
    class UnMaskedAction {
    
    public:
        
        // RESETHAND is handled explicitly
        // the child ones are handled implicitly,
        // since Handler skips SIGCHLD since it's default disposition is Ign
        static constexpr u32 handledFlags = flag::resetBefore | flag::child::no::stop | flag::child::no::wait;
    
    private:
        
        union {
            mutable Const integralHandler;
            Raw handler;
            RawAction action;
        };
        mutable u32 flags;
        // skip sigset_t mask b/c pretty large and already taken care of
        // b/c copied into replacement sigaction
        
        constexpr bool isHandler() const noexcept {
            return !(flags & flag::isAction);
        }
    
    public:
        
        constexpr bool ignores() const noexcept {
            return isHandler() && integralHandler == Const::ignore;
        }
        
        constexpr bool defaults() const noexcept {
            return isHandler() && integralHandler == Const::default_;
        }
        
        constexpr bool hasAction(RawAction _action) const noexcept {
            return !isHandler() && action == _action;
        }
        
        explicit constexpr UnMaskedAction(Const integralHandler, u32 flags = 0) noexcept
                : integralHandler(integralHandler), flags(flags & ~flag::isAction) {}
        
        explicit constexpr UnMaskedAction(Raw handler, u32 flags = 0) noexcept
                : handler(handler), flags(flags & ~flag::isAction) {}
        
        explicit constexpr UnMaskedAction(RawAction action, u32 flags = 0) noexcept
                : action(action), flags(flags | flag::isAction) {}
        
        constexpr UnMaskedAction() noexcept : UnMaskedAction(Const::ignore) {}
        
        explicit constexpr UnMaskedAction(const struct sigaction& sigAction) noexcept
                : integralHandler(Const::ignore), flags(sigAction.sa_flags) {
            if (isHandler()) {
                handler = sigAction.sa_handler;
            } else {
                action = sigAction.sa_sigaction;
            }
        }
    
        constexpr void reset() const noexcept {
            flags &= ~flag::isAction;
            integralHandler = Const::ignore;
        }
        
        bool operator()(const Signal& signal) const noexcept;
        
    };
    
}
