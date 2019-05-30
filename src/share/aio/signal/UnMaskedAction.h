//
// Created by Khyber on 5/25/2019.
//

#pragma once

#include "src/share/aio/signal/RawHandler.h"
#include "src/share/aio/signal/Signal.h"
#include "src/share/aio/signal/Flag.h"

namespace aio::signal {
    
    // like sigaction, but no sigset_t mask, which is large
    // doesn't support SIG_DFL either
    // also doesn't store sa_restorer, but that's never used
    class UnMaskedAction {

    public:
        
        // RESETHAND is handled explicitly
        // the child ones are handled implicitly,
        // since Handler skips SIGCHLD since it's default disposition is Ign
        static constexpr u32 handledFlags = flag::resetBefore | flag::child::no::stop | flag::child::no::wait;
        
    private:
        
        union {
            mutable RawSigHandler handler;
            RawActionHandler action;
        };
        mutable u32 flags;
        // skip sigset_t mask b/c pretty large and already taken care of
        // b/c copied into replacement sigaction
        
        constexpr bool isHandler() const noexcept {
            return !(flags & flag::isAction);
        }
    
    public:
        
        bool ignore() const noexcept;
        
        constexpr bool hasAction(RawActionHandler _action) const noexcept {
            return !isHandler() && action == _action;
        }
        
        explicit constexpr UnMaskedAction(RawSigHandler handler, u32 flags = 0) noexcept
                : handler(handler), flags(flags & ~flag::isAction) {}
        
        explicit constexpr UnMaskedAction(RawActionHandler action, u32 flags = 0) noexcept
                : action(action), flags(flags | flag::isAction) {}
        
        UnMaskedAction() noexcept;
        
        explicit constexpr UnMaskedAction(const struct sigaction& sigAction) noexcept
                : action(nullptr), flags(sigAction.sa_flags) {
            if (isHandler()) {
                handler = sigAction.sa_handler;
            } else {
                action = sigAction.sa_sigaction;
            }
        }
        
        void reset() const noexcept;
        
        void operator()(const Signal& signal) const noexcept;
        
    };
    
}
