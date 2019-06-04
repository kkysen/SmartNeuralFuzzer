//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include <unistd.h>

namespace hook::libc {
    
    void onExit() noexcept;
    
    void onExec() noexcept;
    
    void onKill() noexcept;
    
    void onCrash() noexcept;
    
    void onFork(pid_t cpid);
    
    void onSignalWarning(int signal) noexcept;
    
    void onSignalHandlerChange(int signal) noexcept;

}
