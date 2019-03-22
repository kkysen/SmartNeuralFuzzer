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
    
    T& operator()() const {
        if (!instance) {
            instance = std::make_unique<T>();
        }
        return *instance;
    }
    
};
