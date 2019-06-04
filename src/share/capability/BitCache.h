//
// Created by Khyber on 6/4/2019.
//

#pragma once

// this probably should go somewhere else
namespace capability {
    
    struct BitCache {
        
        bool use: 1;
        mutable bool is: 1;
        mutable bool value: 1;
        
        explicit constexpr BitCache(bool use) noexcept : use(use), is(false), value() {}
        
        constexpr BitCache() noexcept : BitCache(false) {}
        
        // need to return const BitCache& b/c method is const
        constexpr const BitCache& operator=(bool _value) const noexcept {
            value = _value;
            is = true;
            return *this;
        }
        
        explicit constexpr operator bool() const noexcept {
            return value;
        }
        
    };
    
}
