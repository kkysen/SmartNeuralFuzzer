//
// Created by Khyber on 5/31/2019.
//

#pragma once

#include <atomic>

namespace concurrent {
    
    class SpinLock {

    private:
        
        std::atomic_flag flag = ATOMIC_FLAG_INIT;

    public:
    
        constexpr void unlock() noexcept {
            flag.clear();
        }
    
        constexpr bool tryLock() noexcept {
            return __builtin_expect(!flag.test_and_set(), false);
        }
    
        constexpr bool try_lock() noexcept {
            return tryLock();
        }
        
        constexpr void lock() noexcept {
            while (!tryLock());
        }
    
    };
    
}
