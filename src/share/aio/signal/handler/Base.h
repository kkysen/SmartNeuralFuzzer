//
// Created by Khyber on 6/5/2019.
//

#pragma once

#include "src/share/aio/signal/handler/Func.h"
#include "src/share/aio/signal/handler/AltStack.h"
#include "src/share/aio/signal/handler/UnMaskedAction.h"
#include "src/share/concurrent/lock/AdaptiveMutex.h"
#include "src/share/stde/reversed.h"

#include "llvm/ADT/SmallVector.h"
#include "Passive.h"


namespace aio::signal::handler {
    
    template <class Impl>
    class Base {

    private:
        
        AltStack altStack;
        llvm::SmallVector<HandlerFunc, 2> handlers;
        
        // doesn't need to be atomic, just volatile to prevent reordering for async signal handlers
        volatile bool currentlyRegistering = false;
        concurrent::AdaptiveMutex<> lock;

    protected:
        
        void ownHandle(const Signal& signal) const noexcept {
            for (const auto& handler : stde::reversed(handlers)) {
                handler(signal);
            }
        }

    private:
        
        void operator()(int signal, siginfo_t* sigInfo, void* context) const noexcept {
            (*this)(Signal(signal, sigInfo, context));
        }
        
        // must be a pure function pointer, so no closures allowed
        // instance is a singleton, no other instances allowed
        static void handle(int signal, siginfo_t* sigInfo, void* context) noexcept {
            get()(signal, sigInfo, context);
        }

    public:
        
        // should only be added at process start,
        // so multi-threaded data races are not a problem
        void add(HandlerFunc&& handler) {
            handlers.push_back(std::move(handler));
        }
    
        // for defining a global that adds a handler
        bool added(HandlerFunc&& handler) {
            add(std::move(handler));
            return true;
        }

    private:
        
        static void registerSigAction(int signal,
                                      const struct sigaction* action, struct sigaction* oldAction) noexcept {
            assert(::sigaction(signal, action, oldAction) == 0);
            // only possible errors can't happen:
            // EFAULT: action or oldAction or not part of address space, but they obviously are
            // EINVAL: invalid signal specified, incl. SIGKILL and SIGSTOP,
            //      but I go through a list of all the signals (dispositions) and skip SIGKILL and SIGSTOP
        }
        
        bool tryAddExisting(int signal, struct sigaction& oldAction) noexcept {
            registerSigAction(signal, nullptr, &oldAction);
            const auto unMasked = UnMaskedAction(oldAction);
            // don't want to add our own main handler as one of the handlers
            const bool shouldSkip = unMasked.hasAction(handle) || Impl::shouldSkip(unMasked);
            if (!shouldSkip) {
                Impl::addExisting(signal, unMasked);
            }
            return !shouldSkip;
        }
        
        void registerFor(int signal, struct sigaction& oldAction, bool reset) noexcept {
            // reset is for unrecoverable signals
            // we want to re-raise the signal after processing, so we need to default it first
            
            // re-use oldAction ref to re-use mask and flags
            auto& action = oldAction;
            action.sa_sigaction = handle;
            auto& flags = reinterpret_cast<u32&>(action.sa_flags);
            // altStack.flag() needs to | directly w/ flags b/c it's overloaded (also does a &~)
            flags = ((altStack.flag() | flags) | flag::isAction) & ~UnMaskedAction::handledFlags;
            flags |= reset ? flag::resetBefore : 0u;
            registerSigAction(signal, &action, nullptr);
            Impl::recordHandledSignal(signal);
        }
        
        bool _tryRegisterFor(const disposition::Default& disposition) noexcept {
            // if the disposition is Ign or Cont, don't need to do anything
            // even if there's a signal handler, it won't terminate b/c of it
            // only if the signal handler calls exit(), which calls destructors
            // if the disposition is Term or Core, then we need to register the signal handler
            // if the disposition is Stop, then we don't need to register the signal handler,
            // b/c the process could be continued,
            // but it might be stopped for a while,
            // so instead of calling destructors, we can just flush data
            // in general, the actual signal handler can decide specifically what to do
            // based on what signal it is
            if (!Impl::shouldRegister(disposition)) {
                return false;
            }
            const int signal = disposition.signal;
            struct sigaction action = {}; // share action across both calls to reuse mask and flags
            const bool shouldRegister = tryAddExisting(signal, action);
            if (!shouldRegister) {
                return false;
            }
            registerFor(signal, action, Impl::shouldResetBefore(disposition));
            return true;
        }
        
        bool tryRegisterFor(const disposition::Default& disposition) noexcept {
            if (currentlyRegistering) {
                return false;
            }
            currentlyRegistering = true;
            std::lock_guard guard(lock);
            const bool retVal = _tryRegisterFor(disposition);
            currentlyRegistering = false;
            return retVal;
        }

    public:
        
        void register_() noexcept {
            // use sigaltstack for sigsegv handler if possible
            for (const auto& disposition : disposition::defaults) {
                tryRegisterFor(disposition); // TODO do I need to use bool return value?
            }
        }
        
        bool registerFor(int signal) noexcept {
            const auto* disposition = disposition::getDefault(signal);
            if (!disposition) {
                return false;
            }
            return tryRegisterFor(*disposition);
        }

    protected:
        
        explicit Base(bool registerImmediately) {
            if (registerImmediately) {
                register_();
            }
        }

    public:
    
        static constexpr Impl& get() noexcept {
            return Impl::instance;
        }
        
    };
    
}
