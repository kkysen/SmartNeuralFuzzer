//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hooks/lifecycle/ThreadLifeCycles.h"

namespace {
    
    namespace self {
    
        pthread_t thread() noexcept {
            return ::pthread_self();
        }
    
        pid_t tid() noexcept {
            return ::gettid();
        }
    
        pid_t pid() noexcept {
            return ::getpid();
        }
        
        void killThread(pid_t tid) noexcept {
            ::tgkill(self::pid(), tid, SIGKILL);
            errno = 0; // ignore errors
        }
        
    }
    
}

namespace hooks::lifecycle {
    
    void ThreadLifeCycles::destructSelf() const noexcept {
        lifeCycles.destruct();
    }
    
    void ThreadLifeCycles::destructOther(pid_t _tid) const noexcept {
        // kill thread to stop it from running
        // we are owned globally, so lifeCycles.destruct() is still valid
        // now it's safe to call lifeCycles.destruct(),
        // b/c the other thread isn't using it concurrently
        self::killThread(_tid);
        lifeCycles.destruct();
    }
    
    void ThreadLifeCycles::destruct() noexcept {
        // need atomic exchange so that only 1 thread can call this at a time
        const auto _tid = tid.exchange(0);
        if (_tid == 0) {
            return;
        }
        if (thread == self::thread()) {
            destructSelf();
        } else {
            destructOther(_tid);
        }
    }
    
    ThreadLifeCycles::~ThreadLifeCycles() {
        destruct();
    }
    
    ThreadLifeCycles::ThreadLifeCycles(LifeCycles& lifeCycles) noexcept
            : lifeCycles(lifeCycles), thread(self::thread()), tid(self::tid()) {}
    
}
