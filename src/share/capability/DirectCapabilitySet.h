//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/fields.h"

namespace capability {
    
    struct DirectCapabilitySet {
    
        #define _(field) bool field: 1
        #define $ _
        Capability_fields()
        #undef $
        #undef _
        
    };
    
}
