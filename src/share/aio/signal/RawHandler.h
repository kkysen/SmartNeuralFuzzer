//
// Created by Khyber on 5/25/2019.
//

#pragma once

#include <csignal>

namespace aio::signal {
    
    using RawSigHandler = void (*)(int);
    using RawActionHandler = void (*)(int, siginfo_t*, void*);
    
}
