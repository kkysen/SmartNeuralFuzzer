//
// Created by Khyber on 5/26/2019.
//

#pragma once

#include "src/share/common/numbers.h"

#include <csignal>

namespace aio::signal::handler::flag {
    
    #define Flag constexpr u32
    
    namespace child::no {
        
        Flag stop = SA_NOCLDSTOP;
        Flag wait = SA_NOCLDWAIT;
        
    }
    
    Flag isAction = SA_SIGINFO;
    Flag useAltStack = SA_ONSTACK;
    Flag restart = SA_RESTART;
    Flag noDefer = SA_NODEFER;
    Flag resetBefore = SA_RESETHAND;
    Flag interrupt = SA_INTERRUPT;
    
    #undef Flag
    
}
