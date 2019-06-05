//
// Created by Khyber on 6/3/2019.
//

#include "src/share/hook/lifecycle/signaling/Receiver.h"

#include "src/share/hook/lifecycle/ProcessLifeCycles.h"

#include <unistd.h>

namespace hook::lifecycle::signaling {
    
    bool Receiver::isValid(const Signal& signal) const noexcept {
        if (signal.signal != constants::signal) {
            return false;
        }
        const auto& info = signal.info;
        return info.signal == constants::signal
               && info.code == constants::code
               && info.rt.value.val<decltype(constants::magicNumber)>() == constants::magicNumber
               && info.rt.pid == getpid()
               && info.rt.uid == getuid();
    }
    
    bool Receiver::operator()(const Signal& signal) const noexcept {
        if (!isValid(signal)) {
            return false;
        }
        ProcessLifeCycles::onThreadDestruction();
        return true;
    }
    
}
