//
// Created by Khyber on 6/1/2019.
//

#include "src/share/common/odrUse.h"

#include <cassert>
#include <cstdint>

void odrUsePointer(const void* pointer) noexcept {
    assert(reinterpret_cast<intptr_t>(pointer) != -1);
}
