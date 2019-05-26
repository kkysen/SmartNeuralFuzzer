//
// Created by Khyber on 5/22/2019.
//

#pragma once

#include "src/share/time/TimeSpec.h"

namespace _time {
    
    class Clock {
    
    public:
        
        enum {
            real = CLOCK_REALTIME,
            monotonic = CLOCK_MONOTONIC,
            boot = CLOCK_BOOTTIME,
            internationalAtomic = CLOCK_TAI,
        };
        struct cpu {
            enum {
                process = CLOCK_PROCESS_CPUTIME_ID,
                thread = CLOCK_THREAD_CPUTIME_ID,
            };
        };
        struct raw {
            enum {
                monotonic = CLOCK_MONOTONIC_RAW,
            };
        };
        struct coarse {
            enum {
                real = CLOCK_REALTIME_COARSE,
                monotonic = CLOCK_MONOTONIC_COARSE,
            };
        };
        struct alarm {
            enum {
                real = CLOCK_REALTIME_ALARM,
                boot = CLOCK_BOOTTIME_ALARM,
            };
        };
    
    private:
        
        const clockid_t id;
    
    public:
        
        /*implicit*/ constexpr Clock(clockid_t id = real) noexcept : id(id) {}
        
        /*implicit*/ constexpr operator clockid_t() noexcept {
            return id;
        }
        
        TimeSpec now() const noexcept;
        
        TimeSpec resolution() const noexcept;
        
        bool set(const TimeSpec& time) const noexcept;
        
    };
    
}

