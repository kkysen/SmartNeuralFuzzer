//
// Created by Khyber on 7/8/2019.
//

#include "src/share/io/BitWriteBuffer.h"

namespace io {
    
    void BitWriteBuffer::writeBuffer(size_t numBytes) noexcept {
        write(buffer.begin(), numBytes);
    }
    
    void BitWriteBuffer::flush() noexcept {
        writeBuffer();
        bitIndex.reset();
    }
    
    void BitWriteBuffer::tryFlush() noexcept {
        if (shouldFlush()) {
            flush();
        }
    }
    
    void BitWriteBuffer::finalFlush() noexcept {
        writeBuffer(math::minBytesForBits(bitIndex.i));
        const auto bitsInLastBytes = bitIndex.byteBitIndex();
        write(&bitsInLastBytes, sizeof(bitsInLastBytes));
    }
    
    BitWriteBuffer::~BitWriteBuffer() noexcept {
        finalFlush();
    }
    
    void BitWriteBuffer::on(bool bit) noexcept {
        buffer[bitIndex.chunkIndex()] |= static_cast<Chunk>(bit) << bitIndex.chunkBitIndex();
        ++bitIndex;
        tryFlush();
    }
    
    void BitWriteBuffer::on(std::pair<u64, u64> bitsPair) noexcept {
        const auto [bits, maxBits] = bitsPair;
        const auto _numBits = numBits<u64>() - static_cast<u8>(__builtin_clzl(maxBits));
        // TODO this is a slow, naive implementation
        for (u8 i = 0u; i < _numBits; i++) {
            on((bits >> i) & 1u);
        }
    }
    
}
