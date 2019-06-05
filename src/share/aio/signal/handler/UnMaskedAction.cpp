//
// Created by Khyber on 5/25/2019.
//

#include "src/share/aio/signal/handler/UnMaskedAction.h"
#include "src/share/aio/signal/handler/Const.h"

#include <cassert>

namespace {
    
    using namespace aio::signal;
    
    bool handle(const Signal& signal, handler::Raw handler) noexcept {
        // don't support SIG_DFL
        switch (handler::Const(handler)) {
            case handler::Const::error:
            case handler::Const::ignore:
            case handler::Const::hold:
            case handler::Const::default_: {
                return false;
            }
            default: {
                handler(signal.signal);
                return true;
            }
        }
    }
    
    bool handle(const Signal& signal, handler::RawAction handler) noexcept {
        const siginfo_t& sigInfo = signal.info;
        const ucontext_t& context = signal.context;
        // TODO why is this casting to an incompatible type?
        // this is just a const_cast
        auto& mutSigInfo = const_cast<siginfo_t&>(sigInfo);
        auto& mutContext = const_cast<ucontext_t&>(context);
        siginfo_t* sigInfoPtr = &mutSigInfo;
        void* contextPtr = &mutContext;
        handler(signal.signal, sigInfoPtr, contextPtr);
        return true;
    }
    
}

namespace aio::signal::handler {
    
    bool UnMaskedAction::operator()(const Signal& signal) const noexcept {
        const bool handled = isHandler() ? handle(signal, handler) : handle(signal, action);
        if (handled && flags & SA_RESETHAND) {
            reset();
        }
        return handled;
    }
    
}
