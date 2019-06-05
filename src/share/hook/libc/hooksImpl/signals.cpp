//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/include.h"

#include "src/share/hook/lifecycle/signaling/signaling.h"
#include "src/share/aio/signal/mask/Mask.h"
#include "src/share/aio/signal/HandlerConst.h"

namespace {
    
    using namespace hook::lifecycle::signaling;
    using namespace aio::signal::mask;
    
    void removeSpecialSignal(How how, const sigset_t* set) noexcept {
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

sighandler_t signal(int signal, sighandler_t handler) noexcept {
//    trace();
    printf("%s(%d)\n", __func__, signal);
    const auto retVal = impl::signal(signal, handler);
    if (handler) {
        // skip nullptr handler that doesn't change anything
        onSignalHandlerChange(signal);
    }
    return retVal;
}

int sigaction(int signal, const struct sigaction* action, struct sigaction* oldAction) noexcept {
//    trace();
    printf("%s(%d)\n", __func__, signal);
    const auto retVal = impl::sigaction(signal, action, oldAction);
    if (action) {
        // skip nullptr action that doesn't change anything
        onSignalHandlerChange(signal);
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
    using aio::signal::HandlerConst;
    switch (HandlerConst(disposition)) {
        case HandlerConst::error:
        case HandlerConst::ignore: {
            break;
        }
        case HandlerConst::hold: {
            if (signal == ::constants::signal) {
                errno = EINVAL;
                return HandlerConst(HandlerConst::error);
            }
            break;
        }
        case HandlerConst::default_:
        default: {
            onSignalHandlerChange(signal);
            break;
        }
    }
    return impl::sigset(signal, disposition);
}

int sighold(int signal) noexcept {
    if (signal == ::constants::signal) {
        errno = EINVAL;
        return -1;
    }
    return impl::sighold(signal);
}
