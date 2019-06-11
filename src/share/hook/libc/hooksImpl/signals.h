//
// Created by Khyber on 6/5/2019.
//

#pragma once

#include <atomic>

namespace hook::libc::signal {
    
    extern std::atomic<bool> disabled;
    
    bool enabled() noexcept;
    
    class Disable {

    public:
        
        Disable() noexcept;
        
        ~Disable();
        
    };
    
    void onWarning(int signal) noexcept;
    
    void onHandlerChange(int signal, const struct sigaction* oldAction) noexcept;
    
}
