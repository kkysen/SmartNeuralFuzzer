//
// Created by Khyber on 5/29/2019.
//

#pragma once

#define def_has_method(method) \
namespace has { \
     \
    template <typename T, typename = void> \
    struct method : public std::false_type {}; \
     \
    template <typename T> \
    struct method<T, std::void_t<decltype(std::declval<T>().method())>> : public std::true_type {}; \
     \
}

