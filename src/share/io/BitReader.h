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
    
        using Data = io::ReadOnlyMappedMemory<u8>;

    private:
    
        Size size;
        bit::Index i;
        Data data;
        
        static constexpr Size getSize(const Data& data) noexcept {
            const auto& view = data.view();
            const auto size = view.size();
            return (size * numBits<u8>()) + view[size - 1];
        }

    public:
        
        explicit constexpr BitReader(Data&& data) noexcept : size(getSize(data)), data(std::move(data)) {}
    
        constexpr bool done() const noexcept {
            return i.i == size;
        }
    
        constexpr bool hasNext() const noexcept {
            return !done();
        }
        
        constexpr bool next() noexcept {
            const bool value = data.view()[i.byteIndex()] >> i.byteBitIndex();
            ++i;
            return value;
        }
        
        constexpr u64 next(u64 maxValue) noexcept {
            const auto _numBits = numBits<u64>() - static_cast<u8>(__builtin_clzl(maxValue));
            // TODO this is a slow, naive implementation
            u64 value = 0;
            for (u8 i = 0; i < _numBits; i++) {
                value |= static_cast<u64>(next()) << i;
            }
            return value;
        }
        
    };
    
}
