//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include "src/share/concurrent/container/ThreadList.h"

namespace hook::lifecycle {
    
    class ProcessLifeCycles {

    private:
        
        using ThreadIDs = concurrent::ThreadList<pid_t>;
        using Own = typename ThreadIDs::Data;
        
        ThreadIDs tids;
        
        Own add();
        
        static ProcessLifeCycles instance;
        
        static constexpr ProcessLifeCycles& get() noexcept {
            return instance;
        }
        
        static thread_local Own own;

    public:
        
        static void onThreadConstruction() noexcept;
        
        static void onThreadDestruction() noexcept;
        
        static bool onProcessConstruction() noexcept;

    private:
        
        void reconstruct();
    
        void destruct() const noexcept;

    public:
        
        static void onProcessReconstruction();
    
        static void onProcessDestruction() noexcept;
        
    };
    
}
