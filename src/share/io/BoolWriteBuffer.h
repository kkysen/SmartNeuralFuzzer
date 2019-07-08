//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/io/Writer.h"
#include "src/share/io/fse.h"
#include "src/share/common/bools.h"

namespace io {
    
    template <class Counts>
    class BoolWriteBuffer {

    private:
    
        using Size = bools::Size;
        using Chunk = bools::Chunk;
    
        static constexpr auto pageSize = fse::page::size::io::constant;
        static constexpr Size bufferByteSize = static_cast<Size>(math::lcm(pageSize, sizeof(Chunk)));
        static constexpr Size bufferSize = bufferByteSize / sizeof(Chunk);
//            static constexpr Size bufferBitSize = bufferByteSize * numBits<u8>();
        
        std::array<Chunk, bufferSize> buffer = {};
        bools::BitIndex bitIndex;
        
        Counts& counts;
        
        const io::Writer write;
        
        void writeBuffer(size_t numBytes = sizeof(buffer)) noexcept {
            write(buffer.begin(), numBytes);
            counts.flush();
        }
        
        void flush() noexcept {
            writeBuffer();
            bitIndex.reset();
        }
        
        constexpr bool shouldFlush() const noexcept {
            return bitIndex.chunkIndex() == buffer.size();
        }
        
        void tryFlush() noexcept {
            if (shouldFlush()) {
                flush();
            }
        }
        
        void finalFlush() noexcept {
            writeBuffer(math::minBytesForBits(bitIndex));
            const auto bitsInLastBytes = bitIndex.byteBitIndex();
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
            buffer[bitIndex.chunkIndex()] |= static_cast<u64>(value) << bitIndex.chunkBitIndex();
            ++bitIndex;
            tryFlush();
        }
    
        BoolWriteBuffer& operator<<(bool value) noexcept {
            on(value);
            return *this;
        }
        
    };
    
}
