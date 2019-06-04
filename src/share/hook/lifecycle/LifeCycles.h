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
        
        LifeCycle& add(std::unique_ptr<LifeCycle>&& object);
        
        void reconstruct() final;
        
        void flush() noexcept final;
        
        void destruct() noexcept final;
        
        ~LifeCycles() final;
        
        void handleSignal(const aio::signal::Signal& signal) noexcept;
    
    private:
        
        static thread_local LifeCycles instance;
    
    public:
        
        static constexpr LifeCycles& get() noexcept {
            return instance;
        }
        
    };
    
}

