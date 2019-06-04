//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/Bound.h"
#include "src/share/capability/IndirectCapabilitySet.h"

namespace capability {
    
    struct BoundSet : public IndirectCapabilitySet<Bound> {};
    
}
