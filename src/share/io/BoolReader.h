//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/io/ReadOnlyMappedMemory.h"
#include "src/share/common/bools.h"

namespace io {
    
    class BoolReader {

    public:
        
        using Chunk = bools::Chunk;
        using Size = bools::Size;
    
        using Data = io::ReadOnlyMappedMemory<u8>;

    private:
    
        Size size;
        bools::BitIndex i;
        Data data;
        
        static constexpr Size getSize(const Data& data) noexcept {
            const auto& view = data.view();
            const auto size = view.size();
            return (size * numBits<u8>()) + view[size - 1];
        }

    public:
        
        explicit constexpr BoolReader(Data&& data) noexcept : size(getSize(data)), data(std::move(data)) {}
    
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
        
    };
    
}
