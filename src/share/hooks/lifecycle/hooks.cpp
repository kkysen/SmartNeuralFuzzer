//
// Created by Khyber on 5/29/2019.
//

#include "src/share/hooks/lifecycle/hooks.h"

#include "src/share/hooks/lifecycle/ThreadLifeCycles.h"

namespace hooks::lifecycle {
    
    LifeCycle& add(std::unique_ptr<LifeCycle>&& object) {
        return thread::lifeCycles.add(std::move(object));
    }
    
}
