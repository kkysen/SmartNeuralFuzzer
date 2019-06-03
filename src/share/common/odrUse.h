//
// Created by Khyber on 6/1/2019.
//

#pragma once

void odrUsePointer(const void* pointer) noexcept;

template <typename T>
void odrUse(const T& t) noexcept {
    return odrUsePointer(&t);
}
