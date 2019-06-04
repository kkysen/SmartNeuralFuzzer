//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hook/lifecycle/ThreadLifeCycles.h"

#include "src/share/common/odrUse.h"

namespace hook::lifecycle::thread {
    
    thread_local LifeCycles lifeCycles;
    
    void construct() noexcept {
        odrUse(lifeCycles);
    }
    
    void reconstruct() {
        lifeCycles.reconstruct();
    }
    
    void destruct() noexcept {
        lifeCycles.destruct();
    }
    
}
