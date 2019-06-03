//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "src/share/hooks/lifecycle/ThreadLifeCyclesOwner.h"
#include "src/share/common/odrUse.h"

namespace hooks::lifecycle {
    
    class ProcessLifeCycles {

    private:
        
        using List = typename ThreadLifeCyclesOwner::List;
        using Lock = typename ThreadLifeCyclesOwner::Lock;
    
        List threads;
        Lock lock = concurrent::Mutex::Init::recursive;
        
        ProcessLifeCycles() noexcept = default;
        
        ThreadLifeCyclesOwner add() {
            return ThreadLifeCyclesOwner(threads, lock);
        }
        
        ~ProcessLifeCycles() {
            // recursive mutex, so this is okay
            // only recursively locks if it was locked by the current thread,
            // which means we're in a signal handler and we're about to die
            // and that the part of the current thread currently holding the lock
            // isn't actively changing the list of threads, so it's safe for us
            // but if another thread is holding the lock,
            // then we block, and since the other thread isn't in a signal handler,
            // it can continue and release the lock soon
            std::lock_guard guard(lock);
            delete &threads;
            // this way we also don't need any signal masks
        }
        
        static ProcessLifeCycles instance;
        
        static ProcessLifeCycles& get() noexcept {
            return instance;
        }
        
        // will destruct at thread death and delete its ThreadLifeCycles from the list
        static thread_local ThreadLifeCyclesOwner owner;

    public:
    
        static void onThreadCreation() {
            // thread_local required to be initialized before first ODR used
            // so here we just "use" it to trick the compiler
            odrUse(owner);
        }
        
        static void onProcessCreation() {
        
        }
        
        static void onProcessDestruction() {
        
        }
    
    };
    
    ProcessLifeCycles ProcessLifeCycles::instance;
    
    thread_local auto ProcessLifeCycles::owner = ProcessLifeCycles::get().add();
    
}
