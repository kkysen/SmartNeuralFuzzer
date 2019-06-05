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
    
    void onSignalWarning(int signal) noexcept {
        const auto* dispositionPtr = aio::signal::disposition::getDefault(signal);
        if (!dispositionPtr) {
            return;
        }
        const auto& disposition = *dispositionPtr;
        if (disposition.isUnstoppable) {
            // normally these are uncatchable (SIGKILL, SIGSTOP),
            // but I'm catching them before they're raised
            // so I have a chance to clean up first
            onKill();
        } else if (disposition.terminates) {
            // only call onCrash() if we're sure the program will exit immediately
            if (hook::libc::impl::signal(signal, nullptr) == SIG_DFL) {
                onKill();
            }
        }
    }
    
    void onSignalHandlerChange(int signal) noexcept {
        if (signal == lifecycle::signaling::constants::signal) {
            // TODO
        }
    }
    
}
