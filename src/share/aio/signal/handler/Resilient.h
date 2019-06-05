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
        
//        friend class Base<Resilient>;
        
        std::array<UnMaskedAction, NSIG> oldHandlers = {};
        std::bitset<disposition::defaults.size()> handledSignals;
        
        void oldHandle(const Signal& signal) const noexcept;
        
        void operator()(const Signal& signal) const noexcept;
    
    private:
    
        static constexpr bool shouldSkip(const UnMaskedAction& action) noexcept {
            return action.ignore();
        }
    
        constexpr void addExisting(int signal, const UnMaskedAction& action) {
            oldHandlers[signal] = action;
        }
    
        constexpr void recordHandledSignal(int signal) noexcept {
            // don't use operator[] b/c it has a non-constexpr proxy
            handledSignals.set(signal, true);
        }
        
        static constexpr bool shouldRegister(const disposition::Default& disposition) noexcept {
            return disposition.atLeastStops;
        }
        
        static constexpr bool shouldResetBefore(const disposition::Default& disposition) noexcept {
            return disposition.isUnrecoverable;
        }
        
    private:
        
        // private constructor so singleton, b/c handler must be global
        explicit Resilient(bool registerImmediately);
    
        static Resilient instance;
        
    };
    
}
