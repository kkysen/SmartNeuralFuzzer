//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hooks/lifecycle/hooks.h"

#include "src/share/stde/reversed.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/IndexedMap.h"
#include "LifeCycles.h"

namespace {
    
    using namespace hooks::lifecycle;
    
    thread_local u32 threadId;
    
    llvm::SmallVector<LifeCycles*, 1> threads;
    
}

namespace hooks::lifecycle {
    
    void onThreadCreation() {
        threadId = threads.size();
        threads.push_back(&LifeCycles::get());
    }
    
    LifeCycle& add(std::unique_ptr<LifeCycle>&& object) {
        return lifeCycles.add(std::move(object));
    }
    
    void reconstruct() {
        for (const auto& e : objects) {
            e->reconstruct();
        }
    }
    
    void flush() noexcept {
        for (const auto& e : stde::reversed(objects)) {
            e->flush();
        }
    }
    
    void destruct() noexcept {
        for (const auto& e : stde::reversed(objects)) {
            e->destruct();
        }
    }
    
    void handleSignal(const aio::signal::Signal& signal) noexcept {
        const auto& disposition = signal.defaultDisposition;
        if (disposition.terminates) {
            destruct();
        } else if (disposition.atLeastStops) {
            flush();
        }
    }
    
}

namespace {
    
    const bool unused = aio::signal::Handler::get().added(hooks::lifecycle::handleSignal);
    
}
