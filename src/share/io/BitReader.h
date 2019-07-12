//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/io/ReadOnlyMappedMemory.h"
#include "src/share/common/bit.h"

namespace io {
    
    class BitReader {

    public:
        
        using Chunk = bit::Chunk;
        using Size = bit::Size;
    
        using Data = io::ReadOnlyMappedMemory<Chunk>;

    private:
    
        Size size;
        bit::Index i;
        Data data;
        
        static constexpr Size getSize(const Data& data) noexcept {
            const auto& view = data.view();
            const auto size = view.size();
            return (size * numBits<Chunk>()) + view[size - 1];
        }

    public:
        
        explicit constexpr BitReader(Data&& data) noexcept : size(getSize(data)), data(std::move(data)) {}
    
        constexpr bool done() const noexcept {
            return i.i == size;
        }
    
        constexpr bool hasNext() const noexcept {
            return !done();
        }

    private:

        constexpr Chunk nextWhenAligned(u8 numBits) noexcept {
            const Chunk value = data.view()[i.chunkIndex()] >> i.chunkBitIndex();
            i.i += numBits;
            return value & (1u << numBits);
        }
        
        constexpr Chunk nextWhenUnAligned(u8 numBits) noexcept {
            const u8 firstNumBits = numBits - i.chunkBitIndex();
            const u8 secondNumBits = numBits - firstNumBits;
            return nextWhenAligned(firstNumBits) | (nextWhenAligned(secondNumBits) << firstNumBits);
        }
        
    public:
        
        constexpr bool next() noexcept {
            return nextWhenAligned(1);
        }
        
        constexpr u64 next(u64 maxValue) noexcept {
            const auto numBits = ::numBits<u64>() - static_cast<u8>(__builtin_clzl(maxValue));
            if (numBits + i.chunkBitIndex() <= ::numBits<Chunk>()) {
                return nextWhenAligned(numBits);
            } else {
                return nextWhenUnAligned(numBits);
            }
        }
        
    };
    
}
