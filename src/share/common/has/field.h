//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include <type_traits>
#include <utility>

#define def_has_field(field) \
namespace has { \
     \
    template <typename T, typename = void> \
    struct field : public std::false_type {}; \
     \
    template <typename T> \
    struct field<T, std::void_t<decltype(std::declval<T>().field)>> : public std::true_type {} \
     \
}
