//
// Created by Khyber on 3/16/2019.
//

#pragma once

#include "src/share/common/numbers.h"

#include <type_traits>

namespace {
    
    template <typename T>
    using Fold = T (*)(const T&, const T&);
    
    // overload operator+ so it can be used in fold expressions
    template <typename T, Fold<T> fold>
    struct Foldable {
        
        T t;
        
        /*implicit*/ constexpr Foldable(T t) noexcept : t(t) {}
        
        /*implicit*/ constexpr operator T() noexcept {
            return t;
        }
        
        constexpr Foldable operator+(const Foldable& other) noexcept {
            return fold(t, other.t);
        }
        
    };
    
}

namespace math {
    
    template <typename T>
    constexpr const T& min(const T& a, const T& b) noexcept {
        return a < b ? a : b;
    }
    
    template <typename T>
    constexpr const T& max(const T& a, const T& b) noexcept {
        return a > b ? a : b;
    }
    
    template <typename ...Ts>
    constexpr std::common_type_t<Ts...> min(Ts... xs) noexcept {
        return (... + Foldable<Ts, min>(xs));
    }
    
    template <typename ...Ts>
    constexpr std::common_type_t<Ts...> max(Ts... xs) noexcept {
        return (... + Foldable<Ts, max>(xs));
    }
    
    template <typename ...Ts>
    constexpr size_t minSize() noexcept {
        return min(sizeof(Ts)...);
    }
    
    template <typename ...Ts>
    constexpr size_t maxSize() noexcept {
        return max(sizeof(Ts)...);
    }
    
    template <typename T>
    constexpr T abs(T t) noexcept {
        return t < 0 ? -t : t;
    }
    
    template <typename T>
    constexpr T difference(T a, T b) noexcept {
        return a < b ? b - a : a - b;
    }
    
    template <typename A, typename B>
    constexpr std::common_type_t<A, B> gcd(A a, B b) noexcept {
        return a == 0 ? abs(b) : b == 0 ? abs(a) : gcd(b, a % b);
    }
    
    template <typename ...Ts>
    constexpr std::common_type_t<Ts...> gcd(Ts... xs) noexcept {
        return (... + Foldable<Ts, gcd>(xs));
    }
    
    template <typename A, typename B>
    constexpr std::common_type_t<A, B> lcm(A a, B b) noexcept {
        return (a == 0 || b == 0) ? 0 : (abs(a) / gcd(a, b)) * abs(b);
    }
    
    template <typename ...Ts>
    constexpr std::common_type_t<Ts...> lcm(Ts... xs) noexcept {
        return (... + Foldable<Ts, lcm>(xs));
    }
    
    template <typename ...Ts>
    constexpr size_t lcmSizeOf() noexcept {
        return lcm(sizeof(Ts)...);
    }
    
    template <typename A, typename B>
    constexpr std::common_type_t<A, B> divUp(A dividend, B divisor) noexcept {
        return (dividend / divisor) + (dividend % divisor == 0);
    }
    
    constexpr size_t minBytesForBits(size_t bits) noexcept {
        return math::divUp(bits, numBits<u8>());
    }
    
    template <typename A, typename B>
    constexpr std::common_type_t<A, B> multipleGreaterThan(A multiple, B greaterThan) noexcept {
        return multiple > greaterThan ? multiple : multiple + multipleGreaterThan(multiple, greaterThan - multiple);
    }
    
    
}
