//
// Created by Khyber on 6/1/2019.
//

#include "src/share/common/odrUse.h"
#include "src/share/common/hardAssert.h"

#include <cstdint>

void odrUsePointer(const void* pointer) noexcept {
    hardAssert(reinterpret_cast<intptr_t>(pointer) != -1);
}
