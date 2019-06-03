//
// Created by Khyber on 5/31/2019.
//

#pragma once

namespace concurrent {
    
    struct NoLock {
        
        constexpr void unlock() const noexcept {}
        
        constexpr bool tryLock() const noexcept {
            return true;
        }
        
        constexpr bool try_lock() const noexcept {
            return tryLock();
        }
        
        constexpr void lock() const noexcept {}
        
    };
    
}
