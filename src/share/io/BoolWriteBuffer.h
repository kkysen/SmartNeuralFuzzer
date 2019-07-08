//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/io/Writer.h"
#include "src/share/io/fse.h"

namespace io {
    
    template <class Counts>
    class BoolWriteBuffer {

    private:
    
        using Size = u32;
        using Chunk = u64;
    
        static constexpr auto pageSize = fse::page::size::io::constant;
        static constexpr Size bufferByteSize = static_cast<Size>(math::lcm(pageSize, sizeof(Chunk)));
        static constexpr Size bufferSize = bufferByteSize / sizeof(Chunk);
//            static constexpr Size bufferBitSize = bufferByteSize * numBits<u8>();
        
        std::array<Chunk, bufferSize> buffer = {};
        Size bitIndex = 0;
        
        Counts& counts;
        
        struct shift {
            
            static constexpr Size byte = 3;
            static_assert((1u << byte) == numBits<u8>());
            
            static constexpr Size chunk = 6;
            static_assert((1u << chunk) == numBits<Chunk>());
            
        };
        
        constexpr Size byteIndex() const noexcept {
            return bitIndex >> shift::byte;
        }
        
        constexpr Size chunkIndex() const noexcept {
            return bitIndex >> shift::chunk;
        }
        
        constexpr u8 byteBitIndex() const noexcept {
            return static_cast<u8>(bitIndex & ((1u << shift::byte) - 1));
        }
        
        constexpr u8 chunkBitIndex() const noexcept {
            return static_cast<u8>(bitIndex & ((1u << shift::chunk) - 1));
        }
        
        const io::Writer write;
        
        void writeBuffer(size_t numBytes = sizeof(buffer)) noexcept {
            write(buffer.begin(), numBytes);
            counts.flush();
        }
        
        void flush() noexcept {
            writeBuffer();
            bitIndex = 0;
        }
        
        constexpr bool shouldFlush() const noexcept {
            return chunkIndex() == buffer.size();
        }
        
        void tryFlush() noexcept {
            if (shouldFlush()) {
                flush();
            }
        }
        
        void finalFlush() noexcept {
            writeBuffer(math::minBytesForBits(bitIndex));
            const u8 bitsInLastBytes = byteBitIndex();
            write(&bitsInLastBytes, sizeof(bitsInLastBytes));
        }
    
    public:
        
        constexpr BoolWriteBuffer(Counts& counts, io::Writer&& write) noexcept
            : counts(counts), write(std::move(write)) {}
            
        ~BoolWriteBuffer() noexcept {
            finalFlush();
        }
        
        void on(bool value) noexcept {
            counts.branches.single++;
            buffer[chunkIndex()] |= static_cast<u64>(value) << chunkBitIndex();
            bitIndex++;
            tryFlush();
        }
    
        BoolWriteBuffer& operator<<(bool value) noexcept {
            on(value);
            return *this;
        }
        
    };
    
}
