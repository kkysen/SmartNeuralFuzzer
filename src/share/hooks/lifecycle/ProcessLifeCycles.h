//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "src/share/hooks/lifecycle/ThreadLifeCycles.h"
#include "src/share/aio/signal/mask/Masker.h"
#include "src/share/concurrent/AdaptiveMutex.h"

#include "llvm/ADT/SmallVector.h"

#include <mutex>
#include <forward_list>

namespace hooks::lifecycle {
    
    using namespace aio::signal::mask;
    using concurrent::AdaptiveMutex;
    
    class ProcessLifeCycles {

    private:
    
        llvm::SmallVector<ThreadLifeCycles, 1> threads;
        AdaptiveMutex<> mutex;
        Mask mask;
        
        std::forward_list<ThreadLifeCycles> list;
        
        ProcessLifeCycles() noexcept : mask(Init::full) {}
        
        void add(LifeCycles& lifeCycles) {
            Masker masker(mask, How::set, Apply::process);
            std::lock_guard guard(mutex); // must acquire lock after mask is set
            threads.emplace_back(lifeCycles);
            list.emplace_front(lifeCycles);
        }
    
    };
    
}
