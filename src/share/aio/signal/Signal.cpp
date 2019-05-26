//
// Created by Khyber on 5/24/2019.
//

#include "src/share/aio/signal/Signal.h"

namespace aio::signal {
    
    Signal::Signal(int signal, const siginfo_t* sigInfo, const void* context) noexcept :
            Signal(signal, Info::of(*sigInfo), *static_cast<const ucontext_t*>(context)) {}
            
}
