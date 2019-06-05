//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hook/libc/hooks.h"

#include "src/share/hook/libc/impl.h"
#include "src/share/hook/lifecycle/ProcessLifeCycles.h"
#include "src/share/hook/lifecycle/signaling/signaling.h"
#include "src/share/aio/signal/Signal.h"

namespace {
    
    using namespace hook::lifecycle;
    
    void reconstruct() {
        ProcessLifeCycles::onProcessReconstruction();
    }
    
    void destruct() noexcept {
        ProcessLifeCycles::onProcessDestruction();
    }
    
}

namespace hook::libc {
    
    void onExit() noexcept {
        destruct();
    }
    
    void onExec() noexcept {
        destruct();
    }
    
    void onKill() noexcept {
        destruct();
    }
    
    void onCrash() noexcept {
        destruct();
    }
    
    void onFork(pid_t cpid) {
        if (!cpid) {
            // if in child
            reconstruct();
        }
    }
    
}
