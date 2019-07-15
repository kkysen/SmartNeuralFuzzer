//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/io/LEB128WriteBuffer.h"
#include "src/share/io/Dir.h"

namespace io {
    
    template <class Buffer>
    class DeltaWriteBuffer {

    private:
    
        Buffer buffer;
        u64 lastIndex = 0;

    public:
    
        void on(u64 value) noexcept {
            const i64 delta = value - lastIndex;
            lastIndex = value;
            buffer << delta;
        }
    
        DeltaWriteBuffer& operator<<(u64 value) noexcept {
            on(value);
            return *this;
        }
    
        explicit constexpr DeltaWriteBuffer(io::Writer&& writer) noexcept(false)
                : buffer(std::move(writer)) {}
        
    };
    
}
