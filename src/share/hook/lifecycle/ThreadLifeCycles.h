//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "src/share/hook/lifecycle/LifeCycles.h"

namespace hook::lifecycle::thread {
    
    extern thread_local LifeCycles lifeCycles;
    
    void construct() noexcept;
    
    void reconstruct();
    
    void destruct() noexcept;
    
}
