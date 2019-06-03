//
// Created by Khyber on 5/31/2019.
//

#pragma once

#include "src/share/hooks/lifecycle/ThreadLifeCycles.h"
#include "src/share/concurrent/AdaptiveMutex.h"

#include <list>

namespace hooks::lifecycle {
    
    class ThreadLifeCyclesOwner {

    public:
        
        using List = std::list<ThreadLifeCycles>;
        using Node = typename List::const_iterator;
        using Lock = concurrent::AdaptiveMutex<concurrent::Mutex>;

    private:
        
        List& list;
        Node node;
        Lock& lock;

    public:
        
        ThreadLifeCyclesOwner(List& list, Lock& lock) : list(list), lock(lock) {
            std::lock_guard guard(lock);
            node = list.emplace(list.end());
        }
        
        deleteCopy(ThreadLifeCyclesOwner);
        
        ~ThreadLifeCyclesOwner() {
            std::lock_guard guard(lock);
            list.erase(node);
        }
        
    };
    
}
