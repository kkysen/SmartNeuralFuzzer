//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/aio/signal/handler/Base.h"

#include "src/share/hook/lifecycle/signaling/Receiver.h"

namespace aio::signal::handler {
    
    /**
     * This is a passive handler because it only registers for signals
     * that don't have an existing handler and have a default disposition that crashes the program.
     * This handler's job is to prevent the program from crashing due to a signal.
     * It has support from hook::libc to re-register for a signal
     * if a signal handler is removed from that signal.
     *
     * It also keeps a special signal, hook::lifecycle::signaling::constants::signal, completely open.
     * That is, it behaves like the Resilient handler in this case,
     * only running the user's signal handler after this one.
     *
     * This passive handler is a last resort handler.
     * Its handlers are only called before the program is about to crash due to a terminating signal,
     * and once they are, it ensures the program definitely crashes.
     * It tries to crash the program in the same exact way to the same thread,
     * but if that doesn't work, then it resorts to raising SIGKILL to the same thread.
     */
    class Passive : public Base<Passive> {
    
    private:
        
        using Super = Base<Passive>;

        friend class Base;
        
        static constexpr auto specialSignal = hook::lifecycle::signaling::constants::signal;
        
        static constexpr auto receiver = hook::lifecycle::signaling::Receiver();
        
        UnMaskedAction oldHandler;
        
        bool oldHandle(const Signal& signal) const noexcept;
        
        void operator()(const Signal& signal) const noexcept;
        
        bool shouldSkip(const UnMaskedAction& action) const noexcept {
            return !action.defaults();
        }
        
        constexpr void addExisting(int signal, const UnMaskedAction& action) {
            if (signal == specialSignal) {
                oldHandler = action;
            }
        }
        
        constexpr void recordHandledSignal(int) const noexcept {}
        
        constexpr bool shouldRegister(const disposition::Default& disposition) const noexcept {
            return disposition.terminates;
        }
        
        constexpr u32 extraFlags(const disposition::Default&) const noexcept {
            return 0;
        }
        
        // private constructor so singleton, b/c handler must be global
        explicit Passive(bool registerImmediately);
        
        static Passive instance;
        
    };
    
}
