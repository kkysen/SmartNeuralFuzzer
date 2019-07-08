//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include "src/share/io/LEB128Reader.h"

namespace io {
    
    class DeltaReader {

    public:
        
        using Data = typename LEB128Reader::Data;

    private:
        
        LEB128Reader reader;
        u64 last = 0;

    public:
    
        explicit constexpr DeltaReader(Data&& data) noexcept : reader(std::move(data)) {}
    
        constexpr bool done() const noexcept {
            return reader.done();
        }
    
        constexpr bool hasNext() const noexcept {
            return reader.hasNext();
        }
    
        constexpr bool hasError() const noexcept {
            return reader.hasError();
        }
    
        constexpr std::string_view error() const noexcept {
            return reader.error();
        }

    private:
    
        constexpr u64 nextUnSigned() noexcept {
            const auto delta = reader.next<i64>();
            const auto current = static_cast<u64>(last + delta);
            last = current;
            return current;
        }

    public:
    
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
