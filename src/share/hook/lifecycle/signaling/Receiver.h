//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include "src/share/hook/lifecycle/signaling/signaling.h"

namespace hook::lifecycle::signaling {
    
    class Receiver {
        
        bool isValid(const Signal& signal) noexcept __attribute__((pure));
        
        bool operator()(const Signal& signal) noexcept;
        
    };
    
}
