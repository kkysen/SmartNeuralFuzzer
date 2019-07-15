//
// Created by Khyber on 7/11/2019.
//

#pragma once

#include "src/share/common/numbers.h"

class Average {

private:
    
    f64 total = 0;
    u64 count = 0;

public:
    
    template <typename T>
    constexpr void on(T t) noexcept {
        total += static_cast<f64>(t);
        count++;
    }
    
    template <typename T>
    constexpr Average& operator<<(T t) noexcept {
        on(t);
        return *this;
    }
    
    constexpr f64 get() const noexcept {
        return total / count;
    }
    
    /*implicit*/ constexpr operator f64() const noexcept {
        return get();
    }
    
};
