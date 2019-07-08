//
// Created by Khyber on 7/8/2019.
//

#include "src/share/io/DeltaWriteBuffer.h"

namespace io {
    
    void DeltaWriteBuffer::on(u64 value) noexcept {
        const i64 delta = value - lastIndex;
        lastIndex = value;
        buffer << delta;
    }
    
    DeltaWriteBuffer& DeltaWriteBuffer::operator<<(u64 value) noexcept {
        on(value);
        return *this;
    }
    
    DeltaWriteBuffer::DeltaWriteBuffer(io::Writer&& writer) noexcept(false)
            : buffer(std::move(writer)) {}
            
}
