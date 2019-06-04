//
// Created by Khyber on 6/4/2019.
//

#include "src/share/capability/AmbientSet.h"

namespace capability {
    
    void AmbientSet::clearCaches() {
        #define $(field) field.resetCache();
        Capability_new()
        #undef $
    }
    
    bool AmbientSet::clear() {
        const bool succeeded = prctl(AmbientClear::all) == 0;
        if (succeeded) {
            clearCaches();
        }
        return succeeded;
    }
    
}
