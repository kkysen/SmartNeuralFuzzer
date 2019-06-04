//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/fields.h"

#include "src/share/common/numbers.h"

namespace capability {
    
    enum class CapabilityAlias : u32 {
        #define _(field) field
        Capability_old(COMMA)
        #undef _
    };
    
    enum class Capability : u32 {
        #define $(field) field
        Capability_new(COMMA)
        #undef $
    };
    
}
