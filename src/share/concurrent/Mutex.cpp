//
// Created by Khyber on 5/31/2019.
//

#include "Mutex.h"

namespace concurrent {
    
    void Mutex::unlock() noexcept {
        mutex.unlock();
    }
    
    bool Mutex::tryLock() noexcept {
        return mutex.try_lock();
    }
    
    bool Mutex::try_lock() noexcept {
        return tryLock();
    }
    
    void Mutex::lock() noexcept {
        mutex.lock();
    }
    
}
