//
// Created by Khyber on 5/23/2019.
//

#include "src/share/aio/signal/handler/Resilient.h"

namespace aio::signal::handler {
    
    void Resilient::oldHandle(const Signal& signal) const noexcept {
        oldHandlers[signal.signal](signal);
    }
    
    void Resilient::operator()(const Signal& signal) const noexcept {
        ownHandle(signal);
        oldHandle(signal);
        // TODO FIXME must unregister before raising
        if (signal.defaultDisposition.isUnrecoverable) {
            ::raise(signal.signal);
        }
    }
    
    bool Resilient::shouldSkip(const UnMaskedAction& action) noexcept {
        return action.ignore();
    }
    
    void Resilient::addExisting(int signal, const UnMaskedAction& action) {
        oldHandlers[signal] = action;
    }
    
    void Resilient::recordHandledSignal(int signal) noexcept {
        handledSignals[signal] = true;
    }
    
    Resilient::Resilient(bool registerImmediately) : Base(registerImmediately) {}
    
    Resilient Resilient::instance(false);
    
}
