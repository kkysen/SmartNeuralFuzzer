//
// Created by Khyber on 4/13/2019.
//

#pragma once

#include <string>

namespace stde {
    
    constexpr const char* c_str(const std::string& s) noexcept {
        return s.c_str();
    }
    
    constexpr char* c_str(std::string& s) noexcept {
        return const_cast<char*>(s.c_str());
    }
    
    constexpr const char* c_str_unchecked(std::string_view sv) noexcept {
        return sv.data();
    }
    
    constexpr bool is_c_str(std::string_view sv) noexcept {
        return sv[sv.size()] == 0;
    }
    
    /**
     * The returned c-string may need to be delete[]ed,
     * but not always, so it's unsafe to delete[] it.
     * Therefore, only use this method before calling exec* or exit family functions,
     * which will free all memory anyways.
     */
    const char* c_str(std::string_view sv) {
        if (is_c_str(sv)) {
            return c_str_unchecked(sv);
        }
        char* s = new char[sv.size() + 1];
        sv.copy(s, sv.size());
        s[sv.size()] = 0;
        return s;
    }
    
}
