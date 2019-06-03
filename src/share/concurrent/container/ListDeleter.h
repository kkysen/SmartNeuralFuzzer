//
// Created by Khyber on 5/31/2019.
//

#pragma once

#include "src/share/concurrent/lock/NoLock.h"
#include "src/share/common/deleteCopy.h"

#include <list>
#include <mutex>

namespace stde {
    
    template <typename T, class Lock = concurrent::NoLock, class Allocator = std::allocator<T>>
    class ListDeleter {
    
    public:
        
        using List = std::list<T, Allocator>;
        using Node = typename List::const_iterator;
    
    private:
        
        List& list;
        const Node node;
        Lock& lock;
    
    public:
        
        constexpr ListDeleter(List& list, Node node, Lock& lock = concurrent::NoLock()) noexcept
                : list(list), node(node), lock(lock) {}
        
        deleteCopy(ListDeleter);
        
        ~ListDeleter() {
            std::lock_guard guard(lock);
            list.erase(node);
        }
        
    };
    
}
