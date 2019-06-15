//
// Created by Khyber on 6/14/2019.
//

#pragma once

#include <string_view>

namespace stde {
    
    // these are in C++20
    
    template <typename T, class Traits = std::char_traits<T>>
    constexpr bool startsWith(std::basic_string_view<T, Traits> s, std::basic_string_view<T, Traits> prefix) {
        return s.substr(0, prefix.size()) == prefix;
    }
    
    template <typename T, class Traits = std::char_traits<T>>
    constexpr bool endsWith(std::basic_string_view<T, Traits> s, std::basic_string_view<T, Traits> suffix) {
        return s.size() >= suffix.size() && s.substr(s.size() - suffix.size()) == suffix;
    }
    
}
