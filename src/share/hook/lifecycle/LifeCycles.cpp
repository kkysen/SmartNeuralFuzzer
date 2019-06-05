//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hook/lifecycle/LifeCycles.h"

#include "src/share/stde/reversed.h"

namespace hook::lifecycle {
    
    LifeCycle& LifeCycles::add(std::unique_ptr<LifeCycle>&& object) {
        objects.push_back(std::move(object));
        return *objects.back();
    }
    
    void LifeCycles::reconstruct() {
        for (const auto& e : objects) {
            e->reconstruct();
        }
    }
    
    void LifeCycles::destruct() noexcept {
        for (const auto& e : stde::reversed(objects)) {
            e->destruct();
        }
        objects.clear();
    }
    
    LifeCycles::~LifeCycles() {
        destruct();
    }
    
    void LifeCycles::handleSignal(const aio::signal::Signal& signal) noexcept {
        const auto& disposition = signal.defaultDisposition;
        if (disposition.terminates) {
            destruct();
        } else if (disposition.atLeastStops) {
            flush();
        }
    }
    
    thread_local LifeCycles LifeCycles::instance;
    
}
