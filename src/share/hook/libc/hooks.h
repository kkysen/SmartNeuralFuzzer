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
    
    void onProcessConstruction(pid_t cpid);
    
    void onThreadConstruction() noexcept;

}
