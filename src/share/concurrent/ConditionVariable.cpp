//
// Created by Khyber on 6/3/2019.
//

#include "src/share/concurrent/ConditionVariable.h"

namespace concurrent {
    
    void ConditionVariable::wait() {
        std::unique_lock lock(mutex);
        cv.wait(lock);
    }
    
    void ConditionVariable::notifyOne() noexcept {
        cv.notify_one();
    }
    
    void ConditionVariable::notifyAll() noexcept {
        cv.notify_all();
    }
    
    void ConditionVariable::Waiter::wait() {
        cv.wait();
    }
    
    void ConditionVariable::Notifier::notifyOne() noexcept {
        cv.notifyOne();
    }
    
    void ConditionVariable::Notifier::notifyAll() noexcept {
        cv.notifyAll();
    }
    
}
