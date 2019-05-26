//
// Created by Khyber on 5/23/2019.
//

#pragma once

#include "src/share/aio/signal/UnMaskedAction.h"
#include "src/share/stde/reversed.h"
#include "src/share/common/numbers.h"

#include "llvm/ADT/SmallVector.h"
#include "AltStack.h"

#include <functional>
#include <bitset>

// signals are async IO b/c they're IO interrupts
namespace aio::signal {
    
    using HandlerFunc = std::function<void(const Signal& signal)>;
    
    class Handler {
    
    private:
        
        AltStack altStack;
        llvm::SmallVector<HandlerFunc, 2> handlers;
        std::array<UnMaskedAction, NSIG> oldHandlers = {};
        std::bitset<disposition::defaults.size()> handledSignals;
        
        void old(const Signal& signal) noexcept;
        
        void operator()(const Signal& signal) noexcept;
        
        void operator()(int signal, siginfo_t* sigInfo, void* context) noexcept;
    
        static void handle(int signal, siginfo_t* sigInfo, void* context) noexcept;
        
    public:
        
        void add(HandlerFunc&& handler);
    
    private:
        
        void addExisting(int signal, const UnMaskedAction& action);
        
        bool tryAddExisting(int signal, struct sigaction& oldAction) noexcept;
        
        void registerFor(int signal, struct sigaction& oldAction) noexcept;
        
        bool tryRegisterFor(const disposition::Default& disposition) noexcept;

    public:
        
        void register_() noexcept;
    
        bool registerFor(int signal) noexcept;

    private:
        
        // private constructor so singleton, b/c handler must be global
        Handler();
    
        static Handler instance;
    
    public:
    
        static constexpr Handler& get() noexcept {
            return instance;
        }
        
    };
    
}
