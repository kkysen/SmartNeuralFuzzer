//
// Created by Khyber on 5/23/2019.
//

#pragma once

#include "src/share/aio/signal/handler/Func.h"
#include "src/share/aio/signal/handler/UnMaskedAction.h"
#include "src/share/aio/signal/handler/AltStack.h"
#include "src/share/stde/reversed.h"
#include "src/share/common/numbers.h"

#include "llvm/ADT/SmallVector.h"

#include <bitset>

// signals are async IO b/c they're IO interrupts
namespace aio::signal::handler {
    
    /**
     * This is a resilient handler b/c it overwrites and wraps existing signal handlers.
     * When combined with support in hook::libc,
     * it can also be re-registered whenever another signal handler overwrites this.
     */
    class Resilient {
    
    private:
        
        AltStack altStack;
        llvm::SmallVector<HandlerFunc, 2> handlers;
        std::array<UnMaskedAction, NSIG> oldHandlers = {};
        std::bitset<disposition::defaults.size()> handledSignals;
        
        void oldHandle(const Signal& signal) const noexcept;
        
        void ownHandle(const Signal& signal) const noexcept;
        
        void operator()(const Signal& signal) const noexcept;
        
        void operator()(int signal, siginfo_t* sigInfo, void* context) const noexcept;
    
        static void handle(int signal, siginfo_t* sigInfo, void* context) noexcept;
        
    public:
        
        void add(HandlerFunc&& handler);
        
        // for defining a global that adds a handler
        bool added(HandlerFunc&& handler);
    
    private:
        
        void addExisting(int signal, const UnMaskedAction& action);
        
        bool tryAddExisting(int signal, struct sigaction& oldAction) noexcept;
        
        void registerFor(int signal, struct sigaction& oldAction, bool reset) noexcept;
        
        bool _tryRegisterFor(const disposition::Default& disposition) noexcept;
        
        bool currentlyRegistering = false; // TODO should this be atomic
        
        bool tryRegisterFor(const disposition::Default& disposition) noexcept;

    public:
        
        void register_() noexcept;
    
        bool registerFor(int signal) noexcept;

    private:
        
        // private constructor so singleton, b/c handler must be global
        Resilient(bool registerImmediately);
    
        static Resilient instance;
    
    public:
    
        static constexpr Resilient& get() noexcept {
            return instance;
        }
        
    };
    
}
