//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include "src/share/hook/lifecycle/LifeCycle.h"
#include "src/share/hook/lifecycle/hooks.h"
#include "src/share/common/has/method.h"

namespace {
    
    def_has_method(flush);
    
}

namespace hook::lifecycle {
    
    template <typename T>
    class LazilyConstructed : public hook::lifecycle::LifeCycle {
    
    public:
    
        ::LazilyConstructed <T> lazy;
        
        void reconstruct() final {
            lazy.reconstruct();
        }
        
        void flush() noexcept final {
            if constexpr (::has::flush<T>()) {
                lazy().flush();
            }
        }
        
        void destruct() noexcept final {
            lazy.destruct();
        }
        
        static ::LazilyConstructed<T>& add() noexcept {
            return lifecycle::add(std::make_unique<LazilyConstructed<T>>()).lazy;
        }
        
    };
    
}
