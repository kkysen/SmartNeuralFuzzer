//
// Created by Khyber on 6/10/2019.
//

#pragma once

#include <string_view>

namespace stde {
    
    template <class F, typename T = char, class Traits = std::char_traits<T>>
    void split(std::basic_string_view<T, Traits> s, T delimiter, F f) noexcept {
        size_t i = 0;
        size_t j = s.find(delimiter);
        while (j != std::basic_string_view<T, Traits>::npos) {
            f(s.substr(i, j - i));
            i = j + 1;
            j = s.find(delimiter, i);
        }
    }
    
    template <class F, typename T = char, class Traits = std::char_traits<T>>
    void split(std::basic_string_view<T, Traits> s, std::basic_string_view<T, Traits> delimiter) noexcept {
        size_t i = 0;
        size_t j = s.find(delimiter);
        while (j != std::basic_string_view<T, Traits>::npos) {
            f(s.substr(i, j - i));
            i = j + delimiter.size();
            j = s.find(delimiter, i);
        }
    }
    
}
