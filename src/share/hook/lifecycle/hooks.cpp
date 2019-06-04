//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hook/lifecycle/hooks.h"

#include "src/share/hook/lifecycle/ThreadLifeCycles.h"

namespace hook::lifecycle {
    
    LifeCycle& add(std::unique_ptr<LifeCycle>&& object) {
        return thread::lifeCycles.add(std::move(object));
    }
    
}
