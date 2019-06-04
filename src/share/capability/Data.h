//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/Capability.h"

#include <linux/capability.h>

namespace capability {
    
    struct Data {
        
        Capability effective;
        Capability permitted;
        Capability inheritable;
    
        using Impl = __user_cap_data_struct;
    
        const Impl& impl() const noexcept;
    
        Impl& impl() noexcept;
    
        /*implicit*/ operator const Impl&() const noexcept;
    
        /*implicit*/ operator Impl&() noexcept;
        
    };
    
}
