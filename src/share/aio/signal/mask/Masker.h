//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "Mask.h"
#include "How.h"

namespace aio::signal::mask {
    
    class Masker {
    
    private:
        
        const Mask& mask;
        const Mask old;
        const Apply apply;
    
    public:
        
        // Apply::process only blocks signals in the current thread,
        // but Apply::thread doesn't block NPTL threading signals;
        // Apply::process blocks everything, so only
        // an unstoppable (SIGKILL, SIGSTOP) or unrecoverable (SIGSEGV, etc.)
        // signal can stop the current thread
        explicit Masker(const Mask& mask, How how, Apply apply = Apply::process) noexcept;
        
        ~Masker();
        
    };
    
}
