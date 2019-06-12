//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/concurrent/lock/AdaptiveMutex.h"
#include "src/share/common/deleteCopy.h"
#include "src/share/concurrent/ConditionVariable.h"

#include <list>
#include <condition_variable>

//#include "src/share/common/debug.h" // TODO remove

namespace concurrent {
    
    template <typename T, class Allocator = std::allocator<T>>
    class ThreadList;
    
    template <typename T, class Allocator = std::allocator<T>>
    class ThreadData {
    
    public:
        
        using List = std::list<T, Allocator>;
        using Node = typename List::const_iterator;
        using Lock = AdaptiveMutex<Mutex<mutex::Init::recursive>>;
    
    private:
        
        List& list;
        Node node;
        Lock& lock;
        ConditionVariable::Notifier noThreadsLeft;
        
        friend class ThreadList<T, Allocator>;
        
        template <class... Args>
        ThreadData(List& list, Lock& lock, ConditionVariable::Notifier noThreadsLeft, Args&& ...args)
                : list(list), lock(lock), noThreadsLeft(noThreadsLeft) {
            std::lock_guard guard(lock);
            node = list.emplace(list.end(), std::forward<Args>(args)...);
        }
    
    public:
        
        deleteCopy(ThreadData);
        
        ThreadData& operator=(ThreadData&& other) noexcept {
            if (this == &other) {
                return *this;
            }
            struct Bytes {
                u8 bytes[sizeof(ThreadData)];
            };
            auto& ownBytes = reinterpret_cast<Bytes&>(*this);
            auto& otherBytes = reinterpret_cast<Bytes&>(static_cast<ThreadData&>(other));
            Bytes tempBytes = ownBytes;
            ownBytes = otherBytes;
            otherBytes = tempBytes;
            return *this;
        }
        
        ~ThreadData() {
            if (list.empty()) {
                // list has been cleared explicitly, so now this ThreadData is dangling
                // dont need to clean up anything, since it's already deleted
                return;
            }
            std::lock_guard guard(lock);
//            using namespace std::literals;
//            _dbg("erasing "s + std::to_string(*node));
            list.erase(node);
            if (list.empty()) {
//                _dbg("notifying");
                // TODO I don't know why this isn't working
                noThreadsLeft.notifyAll();
            }
        }
        
    };
    
    template <typename T, class Allocator>
    class ThreadList {
    
    public:
        
        using Data = ThreadData<T, Allocator>;
        
        using List = typename Data::List;
        using Lock = typename Data::Lock;
    
    private:
        
        List list;
        mutable Lock lock;
        mutable ConditionVariable noThreadsLeft;
    
    public:
    
        constexpr size_t size() const noexcept {
            return list.size();
        }
    
        deleteCopy(ThreadList);
    
        ThreadList() noexcept = default;
        
        ConditionVariable::Waiter onNoThreadsLeft() const noexcept {
            return noThreadsLeft.waiter();
        }
        
        template <class... Args>
        Data add(Args&& ...args) {
            return Data(list, lock, noThreadsLeft.notifier(), std::forward<Args>(args)...);
        }
        
        template <class F>
        void forEach(F f) const noexcept {
            std::lock_guard guard(lock);
//            _dbg(list.size());
            pid_t localList[list.size()];
            size_t i = 0;
            for (const auto e : list) {
                localList[i++] = e;
            }
            for (const auto e : localList) {
                f(e);
            }
        }
        
        template <class F>
        void forEach(F f) noexcept {
            std::lock_guard guard(lock);
            for (const auto& e : list) {
                f(e);
            }
        }
        
        void clear() noexcept {
            std::lock_guard guard(lock);
            list.clear();
        }
        
        ~ThreadList() {
            // recursive mutex, so this is okay
            // only recursively locks if it was locked by the current thread,
            // which means we're in a signal handler and we're about to die
            // and that the part of the current thread currently holding the lock
            // isn't actively changing the list of threads, so it's safe for us
            // but if another thread is holding the lock,
            // then we block, and since the other thread isn't in a signal handler,
            // it can continue and release the lock soon
            std::lock_guard guard(lock);
            list.~List();
            // this way we also don't need any signal masks
        }
        
    };
    
}
