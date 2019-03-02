//
// Created by Khyber on 2/4/2019.
//

#pragma once

#include <cstddef>
#include <iostream>

#include "numbers.h"

class Tracer {

public:
    
    using Guard = u32;

private:
    
    struct Guards {
        
        const Guard* begin = nullptr;
        const Guard* end = nullptr;
    
        constexpr size_t size() const noexcept {
            return end - begin;
        }
    
        constexpr Guards() noexcept = default;
        
        constexpr Guards(Guard* begin, const Guard* end) noexcept
                : begin(begin), end(end) {
            const auto numGuards = size();
            if (numGuards == 0 || *begin) {
                return; // only initialize once
            }
            printf("Guards::Guards: initializing %p..%p\n", begin, end);
//            std::cout << "initializing " << begin << ".." << end << std::endl;
            for (Guard guard = 0; guard < numGuards; guard++) {
                begin[guard] = guard + 1;
            }
        }
        
    };
    
    Guards guards;

public:
    
    constexpr Tracer() noexcept = default;
    
    constexpr void init(Guard* begin, const Guard* end) noexcept {
        guards = Guards(begin, end);
    }
    
    void mark(Guard* guard);
    
};

