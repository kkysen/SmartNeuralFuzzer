//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "src/share/hook/lifecycle/LifeCycle.h"
#include "src/share/aio/signal/Signal.h"

#include "llvm/ADT/SmallVector.h"

namespace hook::lifecycle {
    
    class LifeCycles : public LifeCycle {
    
    private:
        
        llvm::SmallVector<std::unique_ptr<LifeCycle>, 2> objects;
    
    public:
        
        // llvm::SmallVector() is noexcept, it just isn't declared
        LifeCycles() noexcept : objects() {};
        
        deleteCopy(LifeCycles);
        
        template <class LifeCycleImpl>
        LifeCycleImpl& add(std::unique_ptr<LifeCycleImpl>&& object) {
            objects.push_back(std::move(object));
            return static_cast<LifeCycleImpl&>(*objects.back());
        }
        
        void reconstruct() final;
        
        void destruct() noexcept final;
        
        ~LifeCycles() final;
        
    };
    
}

