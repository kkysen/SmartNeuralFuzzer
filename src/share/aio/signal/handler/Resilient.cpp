//
// Created by Khyber on 5/23/2019.
//

#include "src/share/aio/signal/handler/Resilient.h"

namespace aio::signal::handler {
    
    bool Resilient::oldHandle(const Signal& signal) const noexcept {
        return oldHandlers[signal.signal](signal);
    }
    
    void Resilient::operator()(const Signal& signal) const noexcept {
        ownHandle(signal);
        if (!oldHandle(signal)) {
            // if there was no old signal, then we should've crashed here
            reRaise(signal);
        }
    }
    
    Resilient::Resilient(bool registerImmediately) : Base(registerImmediately) {}
    
    Resilient Resilient::instance(false);
    
}
