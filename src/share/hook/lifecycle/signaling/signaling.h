//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include "src/share/aio/signal/Signal.h"

namespace hook::lifecycle::signaling {
    
    using namespace aio::signal;
    
    namespace constants {
    
        constexpr int signal = SIGILL;
        constexpr int code = SI_QUEUE;
    
        extern u64 magicNumber;
        
    }
    
}
