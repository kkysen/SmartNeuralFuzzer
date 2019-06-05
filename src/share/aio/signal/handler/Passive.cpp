//
// Created by Khyber on 6/4/2019.
//

#include "src/share/aio/signal/handler/Passive.h"

#include "src/share/hook/lifecycle/signaling/Receiver.h"
#include "src/share/hook/libc/syscall/sigqueueinfo.h"
#include "src/share/hook/libc/syscall/gettid.h"

#include <thread>

namespace aio::signal::handler {
    
    bool Passive::oldHandle(const Signal& signal) const noexcept {
        return oldHandler(signal);
        // TODO might be better to completely re-install oldHandler
        // TODO but it's a lot more complicated, so I won't bother for now
    }
    
    void Passive::reRaise(const Signal& signal) noexcept {
        // if not handled as a special signal or a user's signal handler,
        // after we ran our own signal handler,
        // we want to re-raise the signal exactly the same
        // with rt_tgsigqueueinfo, we can re-raise the same signal
        // w/ the exact same siginfo_t and to the same thread
        // since we're sending to the same thread,
        // this thread won't have time to concurrently mask the signal
        unRegister(signal.signal);
        ::rt_tgsigqueueinfo(getpid(), gettid(), signal.signal,
                            &const_cast<siginfo_t&>(signal.info.impl()));
        
        // in the off chance we aren't killed after a short amount of time,
        // here we make sure we definitely die using SIGKILL
        using namespace std::literals;
        std::this_thread::sleep_for(10ms);
        hook::libc::impl::raise(SIGKILL);
        
        // try again using _exit()
        // this also makes this function noreturn, which it should be
        std::this_thread::sleep_for(10ms);
        hook::libc::impl::_exit(signal.signal);
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
