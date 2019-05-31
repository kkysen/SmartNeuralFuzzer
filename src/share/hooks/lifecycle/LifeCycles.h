//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "src/share/hooks/lifecycle/LifeCycle.h"
#include "src/share/aio/signal/Signal.h"

#include "llvm/ADT/SmallVector.h"

namespace hooks::lifecycle {
    
    class LifeCycles : public LifeCycle {

    private:
    
        llvm::SmallVector<std::unique_ptr<LifeCycle>, 2> objects;
        
    public:
        
        deleteCopy(LifeCycles);
        
        LifeCycle& add(std::unique_ptr<LifeCycle>&& object);
        
        void reconstruct() final;
        
        void flush() noexcept final;
        
        void destruct() noexcept final;
        
        void handleSignal(const aio::signal::Signal& signal) noexcept;

    private:
        
        static thread_local LifeCycles instance;

    public:
        
        static constexpr LifeCycles& get() noexcept {
            return instance;
        }
        
    };
    
}

