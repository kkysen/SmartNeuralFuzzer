//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/Capability.h"
#include "src/share/capability/fields.h"

namespace capability {
    
    template <template <Capability> class CapabilityType>
    struct IndirectCapabilitySet {
    
        #define _(field) CapabilityType<static_cast<Capability>(CapabilityAlias::field)> field
        #define $(field) CapabilityType<Capability::field> field
        Capability_fields()
        #undef $
        #undef _
    
        #define $(field) field()
        constexpr IndirectCapabilitySet() noexcept : Capability_new(COMMA) {};
        #undef $
        
    };
    
}
