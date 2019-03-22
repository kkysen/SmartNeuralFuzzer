//
// Created by Khyber on 1/17/2019.
//

#pragma once

#include <cstdint>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <climits>

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

namespace fast {
    
    using u8 = std::uint_fast8_t;
    using u16 = std::uint_fast16_t;
    using u32 = std::uint_fast32_t;
    using u64 = std::uint_fast64_t;
    
    using i8 = std::int_fast8_t;
    using i16 = std::int_fast16_t;
    using i32 = std::int_fast32_t;
    using i64 = std::int_fast64_t;
    
}

namespace least {
    
    using u8 = std::uint_least8_t;
    using u16 = std::uint_least16_t;
    using u32 = std::uint_least32_t;
    using u64 = std::uint_least64_t;
    
    using i8 = std::int_least8_t;
    using i16 = std::int_least16_t;
    using i32 = std::int_least32_t;
    using i64 = std::int_least64_t;
    
}

using f32 = float;
using f64 = double;
using f128 = long double;


template <typename T>
constexpr u8 numBits() noexcept {
    return sizeof(T) * CHAR_BIT;
}

template <>
constexpr u8 numBits<bool>() noexcept {
    return 1;
};
