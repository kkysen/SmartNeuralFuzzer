//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/io/Writer.h"
#include "src/share/io/fse.h"
#include "src/share/common/bit.h"

namespace io {
    
    class BitWriteBuffer {

    private:
    
        using Size = bit::Size;
        using Chunk = bit::Chunk;
    
        static constexpr auto pageSize = fse::page::size::io::constant;
        static constexpr Size bufferByteSize = static_cast<Size>(math::lcm(pageSize, sizeof(Chunk)));
        static constexpr Size bufferSize = bufferByteSize / sizeof(Chunk);
//            static constexpr Size bufferBitSize = bufferByteSize * numBits<u8>();
        
        std::array<Chunk, bufferSize> buffer = {};
        bit::Index i;
        
        const io::Writer write;
        
        void writeBuffer(size_t numBytes = sizeof(buffer)) noexcept;
        
        void flush() noexcept;
        
        constexpr bool shouldFlush() const noexcept {
            return i.chunkIndex() == buffer.size();
        }
        
        void tryFlush() noexcept;
        
        void finalFlush() noexcept;
    
    public:
        
        explicit constexpr BitWriteBuffer(io::Writer&& write) noexcept : write(std::move(write)) {}
            
        ~BitWriteBuffer() noexcept;
        
        void on(bool bit) noexcept;
    
    private:
    
        void onWhenAligned(u64 bits, u8 numBits) noexcept;
        
        void onWhenUnAligned(u64 bits, u8 numBits) noexcept;
        
    public:
        
        void on(std::pair<u64, u64> bits) noexcept;
        
        template <typename T>
        BitWriteBuffer& operator<<(T t) noexcept {
            on(t);
            return *this;
        }
        
    };
    
}
