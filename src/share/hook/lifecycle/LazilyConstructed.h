//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include "src/share/hook/lifecycle/LifeCycle.h"
#include "src/share/hook/lifecycle/hooks.h"
#include "src/share/common/has/method.h"

namespace hook::lifecycle {
    
    template <typename T>
    class LazilyConstructed : public LifeCycle {
    
    public:
    
        ::LazilyConstructed <T> lazy;
        
        void reconstruct() final {
            lazy.reconstruct();
        }
        
        void destruct() noexcept final {
            lazy.destruct();
        }
        
        static ::LazilyConstructed<T>& add() noexcept {
            return lifecycle::add(std::make_unique<LazilyConstructed<T>>()).lazy;
        }
        
    };
    
}
