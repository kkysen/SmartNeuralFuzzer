//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/signals.h"

#include "src/share/hook/libc/hooksImpl/include.h"

#include "src/share/hook/lifecycle/signaling/signaling.h"
#include "src/share/aio/signal/mask/Mask.h"
#include "src/share/aio/signal/handler/Const.h"

namespace {
    
    using namespace hook::libc::signal;
    using namespace hook::lifecycle::signaling;
    using namespace aio::signal::mask;
    
    bool isSpecialSignal(int signal) noexcept {
        return enabled() && signal == constants::signal;
    }
    
    void removeSpecialSignal(How how, const sigset_t* set) noexcept {
        if (disabled) {
            return;
        }
        if (set && (how == How::set || how == How::add)) {
            auto mask = Mask(*set);
            mask -= constants::signal;
            const_cast<sigset_t&>(*set) = mask;
        }
    }
    
    void removeSpecialSignal(int how, const sigset_t* set) noexcept {
        removeSpecialSignal(static_cast<How>(how), set);
    }
    
}

namespace hook::libc::signal {
    
    std::atomic<bool> disabled = false;
    
    bool enabled() noexcept {
        return !hook::libc::signal::disabled;
    }
    
    Disable::Disable() noexcept {
        disabled = true;
    }
    
    Disable::~Disable() {
        disabled = false;
    }
    
    void onWarning(int signal) noexcept {
        if (disabled) {
            return;
        }
        const auto* dispositionPtr = aio::signal::disposition::getDefault(signal);
        if (!dispositionPtr) {
            return;
        }
        const auto& disposition = *dispositionPtr;
        if (disposition.isUnstoppable) {
            // normally these are uncatchable (SIGKILL, SIGSTOP),
            // but I'm catching them before they're raised
            // so I have a chance to clean up first
            onKill();
        } else if (disposition.terminates) {
            // only call onCrash() if we're sure the program will exit immediately
            Disable disable;
            if (::signal(signal, nullptr) == SIG_DFL) {
                onKill();
            }
        }
    }
    
    void onHandlerChange(int signal) noexcept {
        if (!isSpecialSignal(signal)) {
            return;
        }
        // TODO
    }
    
}

sighandler_t signal(int signal, sighandler_t handler) noexcept {
//    trace();
    printf("%s(%d)\n", __func__, signal);
    const auto retVal = impl::signal(signal, handler);
    if (handler) {
        // skip nullptr handler that doesn't change anything
        signal::onHandlerChange(signal);
    }
    return retVal;
}

int sigaction(int signal, const struct sigaction* action, struct sigaction* oldAction) noexcept {
//    trace();
    printf("%s(%d)\n", __func__, signal);
    const auto retVal = impl::sigaction(signal, action, oldAction);
    if (action) {
        // skip nullptr action that doesn't change anything
        signal::onHandlerChange(signal);
        removeSpecialSignal(How::set, &action->sa_mask);
    }
    return retVal;
}


int sigprocmask(int how, const sigset_t* set, sigset_t* oldSet) noexcept {
    removeSpecialSignal(how, set);
    return impl::sigprocmask(how, set, oldSet);
}

int pthread_sigmask(int how, const sigset_t* set, sigset_t* oldSet) noexcept {
    removeSpecialSignal(how, set);
    return impl::pthread_sigmask(how, set, oldSet);
}


sighandler_t sigset(int signal, sighandler_t disposition) noexcept {
    using aio::signal::handler::Const;
    switch (handler::Const(disposition)) {
        case handler::Const::error:
        case handler::Const::ignore: {
            break;
        }
        case handler::Const::hold: {
            if (isSpecialSignal(signal)) {
                errno = EINVAL;
                return handler::Const(handler::Const::error);
            }
            break;
        }
        case handler::Const::default_:
        default: {
            signal::onHandlerChange(signal);
            break;
        }
    }
    return impl::sigset(signal, disposition);
}

int sighold(int signal) noexcept {
    if (isSpecialSignal(signal)) {
        errno = EINVAL;
        return -1;
    }
    return impl::sighold(signal);
}
