//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include <csignal>

namespace aio::signal::mask {
    
    enum class How {
        add = SIG_BLOCK,
        remove = SIG_UNBLOCK,
        set = SIG_SETMASK,
    };
    
}
