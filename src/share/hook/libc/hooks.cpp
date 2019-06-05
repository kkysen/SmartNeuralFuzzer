//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hook/libc/hooks.h"

#include "src/share/hook/libc/impl.h"
#include "src/share/hook/lifecycle/ProcessLifeCycles.h"
#include "src/share/hook/lifecycle/signaling/signaling.h"
#include "src/share/aio/signal/handler/Passive.h"

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
    
    void onProcessConstruction(pid_t cpid) {
        if (!cpid) {
            // if in child
            reconstruct();
        }
    }
    
    void onThreadConstruction() noexcept {
        ProcessLifeCycles::onThreadConstruction();
    }
    
}

namespace {
    
    using aio::signal::handler::Passive;
    using hook::libc::onCrash;
    
    const auto unused = Passive::get().added(onCrash);
    
}
