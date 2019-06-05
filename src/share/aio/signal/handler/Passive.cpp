//
// Created by Khyber on 6/4/2019.
//

#include "src/share/aio/signal/handler/Passive.h"

#include "src/share/hook/lifecycle/signaling/Receiver.h"

#include <thread>

namespace aio::signal::handler {
    
    bool Passive::oldHandle(const Signal& signal) const noexcept {
        return oldHandler(signal);
        // TODO might be better to completely re-install oldHandler
        // TODO but it's a lot more complicated, so I won't bother for now
    }
    
    void Passive::operator()(const Signal& signal) const noexcept {
        if (receiver(signal)) {
            return;
        } else if (signal.signal == specialSignal) {
            if (oldHandle(signal)) {
                return;
            }
        } else {
            ownHandle(signal);
        }
        reRaise(signal);
    }
    
    Passive::Passive(bool registerImmediately) : Base(registerImmediately) {}
    
    Passive Passive::instance(true);
    
}
