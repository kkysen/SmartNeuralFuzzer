//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/io/LEB128WriteBuffer.h"
#include "src/share/io/Dir.h"

namespace io {
    
    class DeltaWriteBuffer {

    private:
    
        io::LEB128WriteBuffer buffer;
        u64 lastIndex = 0;

    public:
    
        void on(u64 value) noexcept;
    
        DeltaWriteBuffer& operator<<(u64 value) noexcept;
    
        explicit DeltaWriteBuffer(io::Writer&& writer) noexcept(false);
        
    };
    
}
