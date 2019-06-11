//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include "src/share/common/lazy.h"
#include "src/share/common/deleteCopy.h"

namespace hook::lifecycle {
    
    class LifeCycle {
    
    public:
        
        LifeCycle() noexcept = default;
        
        deleteCopy(LifeCycle);
        
        // these 2 methods must be idempotent
        
        virtual void reconstruct() = 0;
        
        virtual void destruct() noexcept = 0;
        
        // actual destructor should just do the same as destruct,
        // but doesn't have to be idempotent (not part of API)
        virtual ~LifeCycle() {};
        
    };
    
}
