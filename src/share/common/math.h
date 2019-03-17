//
// Created by Khyber on 3/16/2019.
//

#pragma once

template <typename T>
constexpr T divUp(T dividend, T divisor) noexcept {
    return (dividend / divisor) + (dividend % divisor == 0);
}

template <typename T>
constexpr T multipleGreaterThan(T multiple, T greaterThan) noexcept {
    return multiple > greaterThan ? multiple : multiple + multipleGreaterThan(multiple, greaterThan - multiple);
}
