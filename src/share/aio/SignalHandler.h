//
// Created by Khyber on 5/23/2019.
//

#pragma once

#include "src/share/aio/Signal.h"
#include "src/share/stde/reversed.h"

#include <llvm/ADT/SmallVector.h>

#include <functional>
#include <csignal>
#include <src/share/common/numbers.h>

// signals are async IO b/c they're IO interrupts
namespace aio {
    
    using RawSignalHandler = void(*)(int);
    using RawSigActionHandler = void(*)(int, siginfo_t*, void*);
    using SignalHandlerFunc = std::function<void(const Signal& signal)>;
    
    class SignalHandler {
    
    private:
        
        static_assert(SIGSTKSZ >= MINSIGSTKSZ);
        mutable std::array<u8, SIGSTKSZ> alternateStack = {};
        
        llvm::SmallVector<SignalHandlerFunc, 2> handlers;
        
        constexpr void handle(const Signal& signal) noexcept {
            for (const auto& handler : stde::reversed(handlers)) {
                handler(signal);
            }
        }
        
        constexpr void handle(int signal, siginfo_t* sigInfo, void* context) noexcept {
            handle(Signal(signal, sigInfo, context));
        }
        
        constexpr size_t size() const noexcept {
            return handlers.size();
        }
        
        void add(SignalHandlerFunc&& handler, size_t index);
        
        void add(struct sigaction action, size_t index);

    public:
        
        void add(SignalHandlerFunc&& handler);
    
        void add(struct sigaction action);
        
    private:
        
        // add to beginning so it runs last
        void addExisting(struct sigaction action);
        
        bool registerSigAltStack(int flags) const noexcept;
        
        bool registerSigAltStack() const noexcept;
    
    public:
        
        void register_() const {
            registerSigAltStack();
            
            const int signals[] = {};
            for (const int signal : signals) {
                // need to check if disposition is Term, Core, or Stop so I can add my signal handler
            }
            
            const struct sigaction sigaction = {
                    .sa_sigaction = [](int signal, siginfo_t* sigInfo, void* context) {
                        return instance.handle(signal, sigInfo, context);
                    },
                    .sa_flags = 0, // TODO
                    .sa_mask = {}, // TODO
            };
        }
    
    private:
        
        SignalHandler() {
            register_();
        }
    
    public:
        
        static SignalHandler instance;
        
    };
    
}
