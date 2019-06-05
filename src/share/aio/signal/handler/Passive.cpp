//
// Created by Khyber on 6/4/2019.
//

#include "src/share/aio/signal/handler/Passive.h"

#include "src/share/hook/lifecycle/signaling/Receiver.h"

namespace aio::signal::handler {
    
    void Passive::oldHandle(const Signal& signal) const noexcept {
        // TODO
    }
    
    void Passive::operator()(const Signal& signal) const noexcept {
        if (receiver(signal)) {
            return;
        } else if (signal.signal == specialSignal) {
            oldHandle(signal);
        } else {
            ownHandle(signal);
        }
    }
    
    Passive::Passive(bool registerImmediately) : Base(registerImmediately) {}
    
    Passive Passive::instance(true);
    
}
