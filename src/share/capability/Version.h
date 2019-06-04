//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/common/numbers.h"

#include <linux/capability.h>

namespace capability {
    
    enum class Version : u32 {
        v1 = _LINUX_CAPABILITY_VERSION_1,
        v2 = _LINUX_CAPABILITY_VERSION_2,
        v3 = _LINUX_CAPABILITY_VERSION_3,
    };
    
    extern const Version preferredVersion;
    
}
