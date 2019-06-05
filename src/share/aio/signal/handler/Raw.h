//
// Created by Khyber on 5/25/2019.
//

#pragma once

#include <csignal>

namespace aio::signal::handler {
    
    using Raw = void (*)(int);
    using RawAction = void (*)(int, siginfo_t*, void*);
    
}
