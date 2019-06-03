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
    
    void ThreadLifeCycles::killOtherThread(pid_t _tid) const noexcept {
        if (thread != self::thread()) {
            // kill thread to stop it from running
            // we are owned globally, so lifeCycles.destruct() is still valid
            // now it's safe to call lifeCycles.destruct(),
            // b/c the other thread isn't using it concurrently
            self::killThread(_tid);
        }
    }
    
    ThreadLifeCycles::~ThreadLifeCycles() {
        // need atomic exchange so that only 1 thread can call this at a time
        const auto _tid = tid.exchange(0);
        if (_tid == 0) {
            return;
        }
        killOtherThread(_tid);
        lifeCycles.destruct();
    }
    
    ThreadLifeCycles::ThreadLifeCycles() noexcept
            : lifeCycles(), thread(self::thread()), tid(self::tid()) {}
    
}
