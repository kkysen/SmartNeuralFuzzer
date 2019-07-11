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
    
    void BitWriteBuffer::onWhenAligned(u64 bits, u8 numBits) noexcept {
        buffer[bitIndex.chunkIndex()] |= static_cast<Chunk>(bits) << bitIndex.chunkBitIndex();
        bitIndex.i += numBits;
        tryFlush();
    }
    
    void BitWriteBuffer::on(bool bit) noexcept {
        onWhenAligned(static_cast<Chunk>(bit), 1);
    }
    
    void BitWriteBuffer::onWhenUnAligned(u64 bits, u8 numBits) noexcept {
        const u8 firstNumBits = numBits - bitIndex.chunkBitIndex();
        const u8 secondNumBits = numBits - firstNumBits;
        onWhenAligned(bits, firstNumBits);
        onWhenAligned(bits >> firstNumBits, secondNumBits);
    }
    
    void BitWriteBuffer::on(std::pair<u64, u64> bitsPair) noexcept {
        const auto [bits, maxBits] = bitsPair;
        const auto numBits = ::numBits<u64>() - static_cast<u8>(__builtin_clzl(maxBits));
        if (numBits + bitIndex.chunkBitIndex() <= ::numBits<Chunk>()) {
            onWhenAligned(bits, numBits);
        } else {
            onWhenUnAligned(bits, numBits);
        }
    }
    
}
