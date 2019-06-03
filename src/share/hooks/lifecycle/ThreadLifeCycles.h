//
// Created by Khyber on 5/30/2019.
//

#pragma once

#include "src/share/hooks/lifecycle/LifeCycles.h"
#include "src/share/hooks/libc/syscall/gettid.h"
#include "src/share/hooks/libc/syscall/tgkill.h"

#include <atomic>

#include <unistd.h>
#include <pthread.h>
#include <src/share/common/odrUse.h>

namespace hooks::lifecycle::thread {
    
    extern thread_local LifeCycles lifeCycles;
    
    void onCreation() noexcept;
    
    void onDestruction() noexcept;
    
}
