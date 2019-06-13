//
// Created by Khyber on 6/5/2019.
//

#pragma once

#include "src/share/aio/signal/handler/Func.h"
#include "src/share/aio/signal/handler/AltStack.h"
#include "src/share/aio/signal/handler/UnMaskedAction.h"
#include "src/share/aio/signal/mask/Mask.h"
#include "src/share/concurrent/lock/AdaptiveMutex.h"
#include "src/share/hook/libc/hooksImpl/signals.h"
#include "src/share/hook/libc/syscall/getpid.h"
#include "src/share/hook/libc/syscall/gettid.h"
#include "src/share/hook/libc/syscall/sigqueueinfo.h"
#include "src/share/hook/libc/syscall/forceKill.h"
#include "src/share/stde/reversed.h"
#include "src/share/common/hardAssert.h"

#include "llvm/ADT/SmallVector.h"

#include <thread>

#include <unistd.h>

namespace aio::signal::handler {
    
    template <class Impl>
    class Base {
    
    private:
        
        AltStack altStack;
        llvm::SmallVector<HandlerFunc, 2> handlers;
        
        // doesn't need to be atomic, just volatile to prevent reordering for async signal handlers
        volatile bool currentlyRegistering = false;
        concurrent::AdaptiveMutex<> lock;
    
    private:
        
        constexpr const Impl& impl() const noexcept {
            return static_cast<const Impl&>(*this);
        }
        
        constexpr Impl& mutImpl() noexcept {
            return static_cast<Impl&>(*this);
        }
    
    protected:
        
        void ownHandle(const Signal& signal) const noexcept {
            for (const auto& handler : stde::reversed(handlers)) {
                handler(signal);
            }
        }
        
        [[noreturn]] static void reRaise(const Signal& signal) noexcept {
            // We need to unregister ourselves and unmask our signal,
            // so that rt_tgsigqueueinfo will raise the signal immediately,
            // so that the SIGKILL will be sent afterward,
            // If for whatever reason the signal does terminate the process,
            // we send a SIGKILL immediately after, which can't be stopped.
            // We also need to disable the signal hooks
            // so that our syscalls aren't intercepted.
            // By using rt_tgsigqueueinfo, we can re-raise the same signal
            // with the exact same siginfo_t and to the same thread.
            hook::libc::signal::Disable disable;
            const struct sigaction noAction = {
                    .sa_flags = 0,
                    .sa_mask = {},
                    .sa_handler = SIG_DFL,
            };
            sigAction(signal.signal, &noAction, nullptr);
            mask::Mask mask;
            mask += signal.signal;
            mask.process(mask::How::remove);
            const auto pid = syscalls::getpid();
            const auto tid = syscalls::gettid();
            syscalls::rt_tgsigqueueinfo(pid, tid, signal.signal,
                                &const_cast<siginfo_t&>(signal.info.impl()));
            syscalls::forceKill(); // ensure we are killed
        }
    
    private:
        
        void operator()(int signal, siginfo_t* sigInfo, void* context) const noexcept {
            impl()(Signal(signal, sigInfo, context));
        }
        
        // must be a pure function pointer, so no closures allowed
        // instance is a singleton, no other instances allowed
        static void handle(int signal, siginfo_t* sigInfo, void* context) noexcept {
            getBase()(signal, sigInfo, context);
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
        
        void add(std::function<void()>&& handler) {
            add([_handler = std::move(handler)](const Signal&) {
                _handler();
            });
        }
        
        bool added(std::function<void()>&& handler) {
            add(std::move(handler));
            return true;
        }
    
    private:
        
        static void sigAction(
                int signal, const struct sigaction* action, struct sigaction* oldAction) noexcept {
            hook::libc::signal::Disable disable;
                    hardAssert(::sigaction(signal, action, oldAction) == 0);
            // only possible errors can't happen:
            // EFAULT: action or oldAction or not part of address space, but they obviously are
            // EINVAL: invalid signal specified, incl. SIGKILL and SIGSTOP,
            //      but I go through a list of all the signals (dispositions) and skip SIGKILL and SIGSTOP
        }
    
    private:
        
        bool tryAddExisting(int signal, const struct sigaction& oldAction) noexcept {
            const auto unMasked = UnMaskedAction(oldAction);
            // don't want to add our own main handler as one of the handlers
            const bool shouldSkip = unMasked.hasAction(handle) || impl().shouldSkip(unMasked);
            if (!shouldSkip) {
                mutImpl().addExisting(signal, unMasked);
            }
            return !shouldSkip;
        }
        
        void registerFor(int signal, struct sigaction& oldAction, u32 extraFlags) noexcept {
            // reset is for unrecoverable signals
            // we want to re-raise the signal after processing, so we need to default it first
            
            // re-use oldAction ref to re-use mask and flags
            auto& action = oldAction;
            action.sa_sigaction = handle;
            auto& flags = reinterpret_cast<u32&>(action.sa_flags);
            // altStack.flag() needs to | directly w/ flags b/c it's overloaded (also does a &~)
            flags = ((altStack.flag() | flags) | flag::isAction) & ~UnMaskedAction::handledFlags;
            flags |= extraFlags;
            sigAction(signal, &action, nullptr);
            mutImpl().recordHandledSignal(signal);
        }
        
        bool _tryRegisterFor(const disposition::Default& disposition,
                             const struct sigaction* oldAction) noexcept {
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
            const int signal = disposition.signal;
            struct sigaction action = {}; // share action across both calls to reuse mask and flags
            if (!oldAction) {
                sigAction(signal, nullptr, &action);
            }
            const bool shouldRegister = tryAddExisting(signal, oldAction ? *oldAction : action);
            if (!shouldRegister) {
                return false;
            }
            if (oldAction) {
                // don't want to modify oldAction since the user could use it
                action = *oldAction;
            }
            registerFor(signal, action, impl().extraFlags(disposition));
            return true;
        }
        
        bool tryRegisterFor(const disposition::Default& disposition,
                            const struct sigaction* oldAction) noexcept {
            if (!impl().shouldRegister(disposition)) {
                return false;
            }
            if (currentlyRegistering) {
                return false;
            }
            currentlyRegistering = true;
            std::lock_guard guard(lock);
            const bool retVal = _tryRegisterFor(disposition, oldAction);
            currentlyRegistering = false;
            return retVal;
        }
        
        bool tryRegisterFor(const disposition::Default& disposition) noexcept {
            return tryRegisterFor(disposition, nullptr);
        }
    
    public:
        
        void register_() noexcept {
            // use sigaltstack for sigsegv handler if possible
            for (const auto& disposition : disposition::defaults) {
                tryRegisterFor(disposition);
            }
        }
        
        bool registerFor(int signal, const struct sigaction* oldAction) noexcept {
            const auto* disposition = disposition::getDefault(signal);
            if (!disposition) {
                return false;
            }
            return tryRegisterFor(*disposition, oldAction);
        }
        
        bool registerFor(int signal) noexcept {
            return registerFor(signal, nullptr);
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
    
    private:
        
        static constexpr const Base& getBase() noexcept {
            return static_cast<const Base&>(get());
        }
        
    };
    
}
