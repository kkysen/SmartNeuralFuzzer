//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/Capability.h"

#include <sys/prctl.h>

namespace capability {
    
    enum class BoundOption {
        read = PR_CAPBSET_READ,
        drop = PR_CAPBSET_DROP,
    };
    
    int prctl(BoundOption option, Capability capability) noexcept;
    
    enum class AmbientFlag {
        single = PR_CAP_AMBIENT,
    };
    
    enum class AmbientOption {
        IS = PR_CAP_AMBIENT_IS_SET,
        RAISE = PR_CAP_AMBIENT_RAISE,
        LOWER = PR_CAP_AMBIENT_LOWER,
    };
    
    int prctl(AmbientFlag, AmbientOption ambientOption, Capability capability) noexcept;
    
    enum class AmbientClear {
        all = PR_CAP_AMBIENT_CLEAR_ALL,
    };
    
    int prctl(AmbientClear) noexcept;

}
