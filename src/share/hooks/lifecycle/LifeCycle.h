//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include <src/share/common/lazy.h>

namespace hooks::lifecycle {
    
    class LifeCycle {
    
    public:
    
        // these 3 methods must be idempotent
        
        virtual void reconstruct() = 0;
        
        virtual void flush() noexcept = 0;
        
        virtual void destruct() noexcept = 0;
        
        // actual destructor should just do the same as destruct,
        // but doesn't have to be idempotent (not part of API)
        virtual ~LifeCycle() = 0;
        
    };
    
}
