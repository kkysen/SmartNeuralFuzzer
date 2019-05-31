//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "src/share/hooks/lifecycle/LifeCycles.h"
#include "src/share/hooks/libc/syscall/gettid.h"
#include "src/share/hooks/libc/syscall/tgkill.h"

#include <atomic>

#include <unistd.h>
#include <pthread.h>

namespace hooks::lifecycle {
    
    class ThreadLifeCycles {
    
    private:
        
        LifeCycles& lifeCycles;
        const pthread_t thread;
        std::atomic<pid_t> tid;
        
        void destructSelf() const noexcept;
        
        void destructOther(pid_t _tid) const noexcept;
    
    public:
        
        void destruct() noexcept;
        
        ~ThreadLifeCycles();
        
        explicit ThreadLifeCycles(LifeCycles& lifeCycles) noexcept;
        
        // can't be killing thread repeatedly
        // though move constructor might be possible, but unnecessary
        deleteCopy(ThreadLifeCycles);
        
        // should be destructed when a thread dies
        
        // invalidates it so that destruct() won't do anything
        // used to throw away a failed ThreadLifeCycle
        constexpr void invalidate() noexcept {
            tid.store(0);
        }
        
    };
    
}
