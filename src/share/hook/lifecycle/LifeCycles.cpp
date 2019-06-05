//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hook/lifecycle/LifeCycles.h"

#include "src/share/stde/reversed.h"

namespace hook::lifecycle {
    
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
    
}
