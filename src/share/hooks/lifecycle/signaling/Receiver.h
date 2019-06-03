//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include "src/share/hooks/lifecycle/signaling/signaling.h"

namespace hooks::lifecycle::signaling {
    
    class Receiver {
        
        bool isValid(const Signal& signal) noexcept __attribute__((pure));
        
        bool operator()(const Signal& signal) noexcept;
        
    };
    
}
