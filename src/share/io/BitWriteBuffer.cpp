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
        i.reset();
    }
    
    void BitWriteBuffer::tryFlush() noexcept {
        if (shouldFlush()) {
            flush();
        }
    }
    
    void BitWriteBuffer::finalFlush() noexcept {
        writeBuffer(math::minBytesForBits(i.i));
        const Chunk bitsInLastBytes = i.byteBitIndex();
        write(&bitsInLastBytes, sizeof(bitsInLastBytes));
    }
    
    BitWriteBuffer::~BitWriteBuffer() noexcept {
        finalFlush();
    }
    
    void BitWriteBuffer::onWhenAligned(u64 bits, u8 numBits) noexcept {
        buffer[i.chunkIndex()] |= static_cast<Chunk>(bits) << i.chunkBitIndex();
        i.i += numBits;
        tryFlush();
    }
    
    void BitWriteBuffer::onWhenUnAligned(u64 bits, u8 numBits) noexcept {
        const u8 firstNumBits = numBits - i.chunkBitIndex();
        const u8 secondNumBits = numBits - firstNumBits;
        onWhenAligned(bits, firstNumBits);
        onWhenAligned(bits >> firstNumBits, secondNumBits);
    }
    
    void BitWriteBuffer::on(bool bit) noexcept {
        onWhenAligned(static_cast<Chunk>(bit), 1);
    }
    
    void BitWriteBuffer::on(std::pair<u64, u64> bitsPair) noexcept {
        const auto [bits, maxBits] = bitsPair;
        const auto numBits = ::numBits<u64>() - static_cast<u8>(__builtin_clzl(maxBits));
        if (numBits + i.chunkBitIndex() <= ::numBits<Chunk>()) {
            onWhenAligned(bits, numBits);
        } else {
            onWhenUnAligned(bits, numBits);
        }
    }
    
}
