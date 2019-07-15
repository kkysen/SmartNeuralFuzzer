//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/io/ReaderWrapper.h"
#include "src/share/io/LEB128Reader.h"

namespace io {
    
    class DeltaReader : public ReaderWrapper<LEB128Reader> {

    private:
        
        u64 last = 0;

    private:
    
        constexpr u64 nextUnSigned() noexcept {
            const auto delta = reader.next<i64>();
            const auto current = static_cast<u64>(last + delta);
            last = current;
            return current;
        }

    public:
    
        explicit constexpr DeltaReader(Data&& data) noexcept : ReaderWrapper<LEB128Reader>(std::move(data)) {}
    
        template <typename T = u64>
        constexpr T next() noexcept {
            static_assert(!std::is_signed_v<T>);
            return static_cast<T>(nextUnSigned());
        }
    
        template <typename T>
        constexpr DeltaReader& operator>>(T& t) noexcept {
            t = next<T>();
            return *this;
        }
        
    };
    
}
