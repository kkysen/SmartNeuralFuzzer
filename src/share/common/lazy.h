//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include <bits/unique_ptr.h>

template <typename T>
class LazilyConstructed {

private:
    
    mutable std::unique_ptr<T> instance = nullptr;

public:
    
    constexpr LazilyConstructed() noexcept = default;
    
    void reconstruct() const {
        instance = std::make_unique<T>();
    }
    
    void construct() const {
        if (!instance) {
            reconstruct();
        }
    }
    
    void destruct() const {
        instance.release();
    }
    
    T& get() const {
        construct();
        return *instance;
    }
    
    T& operator()() const {
        return get();
    }
    
    T& operator*() const {
        return get();
    }
    
    T* operator->() const {
        return &get();
    }
    
};
