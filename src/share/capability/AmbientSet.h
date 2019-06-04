//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/Ambient.h"
#include "src/share/capability/IndirectCapabilitySet.h"

namespace capability {
    
    class AmbientSet : public IndirectCapabilitySet<Ambient> {

    private:

        void clearCaches();
        
    public:
        
        bool clear();
        
    };
    
}
