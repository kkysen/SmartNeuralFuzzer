//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include "src/share/hook/lifecycle/LifeCycle.h"
#include "src/share/aio/signal/handler/Resilient.h"
#include "src/share/hook/lifecycle/ThreadLifeCycles.h"

namespace hook::lifecycle {
    
    template <class LifeCycleImpl>
    LifeCycleImpl& add(std::unique_ptr<LifeCycleImpl>&& object) {
        return thread::lifeCycles.add(std::move(object));
    }
    
}
