//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hooks/lifecycle/ThreadLifeCycles.h"

namespace hooks::lifecycle::thread {
    
    thread_local LifeCycles lifeCycles;
    
    void onCreation() noexcept {
        odrUse(lifeCycles);
    }
    
    void onDestruction() noexcept {
        delete &lifeCycles;
    }
    
}
