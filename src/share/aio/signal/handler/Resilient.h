//
// Created by Khyber on 5/23/2019.
//

#pragma once

#include "src/share/aio/signal/handler/Base.h"

#include <bitset>

// signals are async IO b/c they're IO interrupts
namespace aio::signal::handler {
    
    /**
     * This is a resilient handler b/c it overwrites and wraps existing signal handlers.
     * When combined with support in hook::libc,
     * it can also be re-registered whenever another signal handler overwrites this.
     */
    class Resilient : public Base<Resilient> {

    private:
        
        using Super = Base<Resilient>;
        
        friend class Base;
        
        std::array<UnMaskedAction, NSIG> oldHandlers = {};
        std::bitset<disposition::defaults.size()> handledSignals;
        
        bool oldHandle(const Signal& signal) const noexcept;
        
        void operator()(const Signal& signal) const noexcept;
        
        constexpr bool shouldSkip(const UnMaskedAction& action) const noexcept {
            return action.ignores();
        }
    
        constexpr void addExisting(int signal, const UnMaskedAction& action) {
            oldHandlers[signal] = action;
        }
    
        constexpr void recordHandledSignal(int signal) noexcept {
            // don't use operator[] b/c it has a non-constexpr proxy
            handledSignals.set(signal, true);
        }
        
        constexpr bool shouldRegister(const disposition::Default& disposition) const noexcept {
            return disposition.atLeastStops;
        }
        
        constexpr u32 extraFlags(const disposition::Default&) const noexcept {
            return 0;
        }
        
        // private constructor so singleton, b/c handler must be global
        explicit Resilient(bool registerImmediately);
    
        static Resilient instance;
        
    };
    
}
