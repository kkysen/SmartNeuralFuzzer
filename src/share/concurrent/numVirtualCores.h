//
// Created by Khyber on 5/31/2019.
//

#pragma once

#include <cstdlib>
#include <sys/sysinfo.h>

namespace concurrent {
    
    const size_t numVirtualCores = ::get_nprocs();
    
    bool isSingleThreaded() noexcept {
        return __builtin_expect(numVirtualCores == 0, false);
    }

}
