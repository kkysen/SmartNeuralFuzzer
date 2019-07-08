//
// Created by Khyber on 6/25/2019.
//

#pragma once

#include "src/share/io/ReadOnlyMappedMemory.h"
#include "src/share/common/numbers.h"

namespace io {
    
    class LEB128Reader {

    public:
        
        using Data = ReadOnlyMappedMemory<u8>;
    
    private:
        
        Data data;
        size_t i = 0;
        mutable std::string_view _error = {};
        
        constexpr const u8* nextData() const noexcept {
            return data.view().data() + i;
        }
        
        constexpr std::pair<const u8*, const u8*> range() const noexcept {
            return {nextData(), data.view().end()};
        }
        
        constexpr void advanceTo(const u8* p) noexcept {
            i += p - nextData();
        }
    
    public:
        
        explicit constexpr LEB128Reader(Data&& data) noexcept : data(std::move(data)) {}
        
        constexpr bool done() const noexcept {
            return i == data.view().size();
        }
        
        constexpr bool hasNext() const noexcept {
            return !done();
        }
        
        constexpr bool hasError() const noexcept {
            return _error.data() != nullptr;
        }
        
        constexpr std::string_view error() const noexcept {
            return _error;
        }
    
    private:
        
        constexpr std::pair<u64, const u8*> rawNextUnSigned() const noexcept {
            const auto[start, end] = range();
            auto p = start;
            
            u64 value = 0;
            u8 shift = 0;
            do {
                if (end && p == end) {
                    _error = "malformed unsigned LEB128, extends past end";
                    return {0, p};
                }
                u64 Slice = *p & 0x7Fu;
                if (shift >= 64 || Slice << shift >> shift != Slice) {
                    _error = "unsigned LEB128 too big for u64";
                    return {0, p};
                }
                value += static_cast<u64>(*p & 0x7Fu) << shift;
                shift += 7;
            } while (*p++ >= 128);
            return {value, p};
        }
        
        constexpr std::pair<i64, const u8*> rawNextSigned() const noexcept {
            const auto[start, end] = range();
            auto p = start;
            
            i64 value = 0;
            u8 shift = 0;
            u8 byte = 0;
            do {
                if (end && p == end) {
                    _error = "malformed signed LEB128, extends past end";
                    return {0, p};
                }
                byte = *p++;
                value |= (static_cast<i64>(byte & 0x7Fu) << shift);
                shift += 7;
            } while (byte >= 128);
            // Sign extend negative numbers if needed.
            if (shift < 64 && (byte & 0x40u))
                value |= (-1ULL) << shift;
            return {value, p};
        }
    
    public:
        
        constexpr u64 nextUnSigned() noexcept {
            const auto[value, p] = rawNextUnSigned();
            advanceTo(p);
            return value;
        }
        
        constexpr i64 nextSigned() noexcept {
            const auto[value, p] = rawNextSigned();
            advanceTo(p);
            return value;
        }
        
        template <typename T>
        constexpr T next() noexcept {
            if constexpr (std::is_signed_v<T>) {
                return static_cast<T>(nextSigned());
            } else {
                return static_cast<T>(nextUnSigned());
            }
        }
        
        template <typename T>
        constexpr LEB128Reader& operator>>(T& t) noexcept {
            t = next<T>();
            return *this;
        }
        
    };
    
}
