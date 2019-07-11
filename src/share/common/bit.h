//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/common/numbers.h"

namespace bit {
    
    using Size = u64;
    using Chunk = u64;
    
    namespace shift {
        
        constexpr Size byte = 3;
        static_assert((1u << byte) == numBits<u8>());
        
        constexpr Size chunk = 6;
        static_assert((1u << chunk) == numBits<Chunk>());
        
    }
    
    struct Index {
        
        Size i = 0;
    
        constexpr Size byteIndex() const noexcept {
            return i >> shift::byte;
        }
    
        constexpr Size chunkIndex() const noexcept {
            return i >> shift::chunk;
        }
    
        constexpr u8 byteBitIndex() const noexcept {
            return static_cast<u8>(i & ((1u << shift::byte) - 1));
        }
    
        constexpr u8 chunkBitIndex() const noexcept {
            return static_cast<u8>(i & ((1u << shift::chunk) - 1));
        }
        
        constexpr Index& operator++() noexcept {
            ++i;
            return *this;
        }
        
        constexpr Index& reset() noexcept {
            i = 0;
            return *this;
        }
        
    };
    
}
