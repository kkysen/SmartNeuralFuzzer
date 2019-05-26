//
// Created by Khyber on 5/25/2019.
//

#include "src/share/aio/signal/UnMaskedAction.h"

#include <cassert>

namespace {
    
    using namespace aio::signal;
    
    void handle(const Signal& signal, RawSigHandler handler) noexcept {
        // don't support SIG_DFL
        if (handler == SIG_IGN || handler == SIG_DFL) {
            return;
        }
        handler(signal.signal);
    }
    
    void handle(const Signal& signal, RawActionHandler handler) noexcept {
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

namespace aio::signal {
    
    UnMaskedAction::UnMaskedAction() noexcept : UnMaskedAction(SIG_IGN) {}
    
    bool UnMaskedAction::ignore() const noexcept {
        return isHandler() && handler == SIG_IGN;
    }
    
    void UnMaskedAction::reset() const noexcept {
        flags &= ~isAction;
        handler = SIG_IGN;
    }
    
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
