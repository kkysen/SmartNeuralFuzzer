//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include "src/share/hook/lifecycle/LifeCycle.h"
#include "src/share/aio/signal/handler/Resilient.h"

namespace hook::lifecycle {
    
    LifeCycle& add(std::unique_ptr<LifeCycle>&& object);
    
}
