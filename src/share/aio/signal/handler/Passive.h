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
     */
    class Passive : public Base<Passive> {

    private:
    
        using Super = Base<Passive>;
    
//        friend class Base<Passive>;
    
        static constexpr auto specialSignal = hook::lifecycle::signaling::constants::signal;
    
        static constexpr auto receiver = hook::lifecycle::signaling::Receiver();
    
        UnMaskedAction oldHandler;
    
        void oldHandle(const Signal& signal) const noexcept;
    
        void operator()(const Signal& signal) const noexcept;

    private:
        
        static bool shouldSkip(const UnMaskedAction& action) noexcept {
            return action != default; // TODO FIXME UnMaskedAction is supposed to never = SIG_DFL
        }
        
        constexpr void addExisting(int signal, const UnMaskedAction& action) {
            if (signal == specialSignal) {
                oldHandler = action;
            }
        }
    
        static constexpr void recordHandledSignal(int) noexcept {}
    
        static constexpr bool shouldRegister(const disposition::Default& disposition) noexcept {
            return disposition.terminates;
        }
    
        static constexpr bool shouldResetBefore(const disposition::Default&) noexcept {
            return true;
        }

    private:
    
        // private constructor so singleton, b/c handler must be global
        explicit Passive(bool registerImmediately);
    
        static Passive instance;
    
    };
    
}
