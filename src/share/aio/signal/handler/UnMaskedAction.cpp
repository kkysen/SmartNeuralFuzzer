//
// Created by Khyber on 5/25/2019.
//

#include "src/share/aio/signal/handler/UnMaskedAction.h"
#include "src/share/aio/signal/handler/Const.h"

#include <cassert>

namespace {
    
    using namespace aio::signal;
    
    void handle(const Signal& signal, handler::Raw handler) noexcept {
        // don't support SIG_DFL
        switch (handler::Const(handler)) {
            case handler::Const::ignore:
            case handler::Const::default_: {
                return;
            }
            default: {
                handler(signal.signal);
            }
        }
    }
    
    void handle(const Signal& signal, handler::RawAction handler) noexcept {
        const siginfo_t& sigInfo = signal.info;
        const ucontext_t& context = signal.context;
        // TODO why is this casting to an incompatible type?
        // this is just a const_cast
        auto& mutSigInfo = const_cast<siginfo_t&>(sigInfo);
        auto& mutContext = const_cast<ucontext_t&>(context);
        siginfo_t* sigInfoPtr = &mutSigInfo;
        void* contextPtr = &mutContext;
        handler(signal.signal, sigInfoPtr, contextPtr);
    }
    
}

namespace aio::signal::handler {
    
    void UnMaskedAction::operator()(const Signal& signal) const noexcept {
        if (isHandler()) {
            handle(signal, handler);
        } else {
            handle(signal, action);
        }
        if (flags & SA_RESETHAND) {
            reset();
        }
    }
    
}
