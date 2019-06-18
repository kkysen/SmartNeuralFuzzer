//
// Created by Khyber on 6/18/2019.
//

#pragma once

#include "src/share/io/WriteBuffer.h"

namespace io {
    
    struct LEB128WriteBuffer {
        
        WriteBuffer<u8> buffer;
        
        u8 on(u64 value, u8 padTo = 0) noexcept;
        
        u8 on(i64 value, u8 padTo = 0) noexcept;
        
        template <typename T>
        u8 on(T t) noexcept {
            if constexpr (std::is_signed_v<T>) {
                return on(static_cast<i64>(t));
            } else {
                return on(static_cast<u64>(t));
            }
        }
        
        template <typename T>
        LEB128WriteBuffer& operator<<(T t) noexcept {
            on(t);
            return *this;
        }
    
        explicit constexpr LEB128WriteBuffer(Writer&& write) noexcept : buffer(std::move(write)) {}
        
    };
    
}
