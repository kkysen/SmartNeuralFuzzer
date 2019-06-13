//
// Created by Khyber on 6/3/2019.
//

#include "src/share/hook/lifecycle/signaling/Receiver.h"

#include "src/share/hook/lifecycle/ProcessLifeCycles.h"
#include "src/share/hook/libc/syscall/getpid.h"
#include "src/share/hook/libc/syscall/getuid.h"

namespace hook::lifecycle::signaling {
    
    bool Receiver::isValid(const Signal& signal) const noexcept {
        if (signal.signal != constants::signal) {
            return false;
        }
        const auto& info = signal.info;
        return info.signal == constants::signal
               && info.code == constants::code
               && info.rt.value == constants::magicNumber
               && info.rt.pid == syscalls::getpid()
               && info.rt.uid == syscalls::getuid();
    }
    
    bool Receiver::operator()(const Signal& signal) const noexcept {
        if (!isValid(signal)) {
            return false;
        }
        ProcessLifeCycles::onThreadDestruction();
        return true;
    }
    
}
