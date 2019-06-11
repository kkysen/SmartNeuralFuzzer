//
// Created by Khyber on 5/31/2019.
//

#pragma once

#include <cstdlib>
#include <sys/sysinfo.h>

namespace concurrent {
    
    extern const size_t numVirtualCores;
    
    bool isSingleThreaded() noexcept;

}
