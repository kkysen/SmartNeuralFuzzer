//
// Created by Khyber on 6/3/2019.
//

#include "src/share/hook/lifecycle/ProcessLifeCycles.h"

#include "src/share/hook/lifecycle/ThreadLifeCycles.h"
#include "src/share/aio/signal/mask/Masked.h"
#include "src/share/hook/lifecycle/signaling/Sender.h"
#include "src/share/hook/libc/syscall/gettid.h"
#include "src/share/hook/libc/syscall/forceKill.h"
#include "src/share/hook/libc/hooksImpl/signals.h"
#include "src/share/common/odrUse.h"

namespace hook::lifecycle {
    
    ProcessLifeCycles::Own ProcessLifeCycles::add() {
        return tids.add(syscalls::gettid());
    }
    
    ProcessLifeCycles ProcessLifeCycles::instance;
    
    thread_local auto ProcessLifeCycles::own = get().add();
    
    void ProcessLifeCycles::onThreadConstruction() noexcept {
        thread::construct();
        odrUse(own);
    }
    
    void ProcessLifeCycles::onThreadDestruction() noexcept {
        thread::destruct();
        own.~Own();
    }
    
    bool ProcessLifeCycles::onProcessConstruction() noexcept {
        onThreadConstruction();
        return true;
    }
    
    void ProcessLifeCycles::reconstruct() {
        tids.clear();
        own = add();
    }
    
    void ProcessLifeCycles::destruct() const noexcept {
        signaling::Sender send;
        tids.forEach([&send](const pid_t tid) {
            send(tid);
        });
//        {
//            libc::signal::Disable disable;
//            constexpr auto specialSignal = signaling::constants::signal;
//            using namespace aio::signal::mask;
//            Mask mask(Init::full);
//            mask -= specialSignal;
//            Masked masked(mask, How::set);
//            for (int signal = 1; signal < _NSIG; signal++) {
//                if (signal != specialSignal) {
//                    ::signal(signal, SIG_DFL);
//                }
//            }
//        }
        using namespace std::literals;
//        tids.onNoThreadsLeft().wait();
        // TODO wait() should work; I'm not sure why it's not
        tids.onNoThreadsLeft().waitFor(100ms);
        // now we've cleaned up all the thread_local ThreadLifeCycles
    }
    
    void ProcessLifeCycles::onProcessReconstruction() {
        get().reconstruct();
        thread::reconstruct();
    }
    
    void ProcessLifeCycles::onProcessDestruction() noexcept {
        get().destruct();
    }
    
}

namespace {
    
    const bool unused = hook::lifecycle::ProcessLifeCycles::onProcessConstruction();
    
}
