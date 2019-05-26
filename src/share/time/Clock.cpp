//
// Created by Khyber on 5/22/2019.
//

#include "src/share/time/Clock.h"

namespace _time {
    
    TimeSpec Clock::now() const noexcept {
        timespec time = {};
        clock_gettime(id, &time);
        return time;
    }
    
    TimeSpec Clock::resolution() const noexcept {
        timespec time = {};
        clock_getres(id, &time);
        return time;
    }
    
    bool Clock::set(const TimeSpec& time) const noexcept {
        const timespec _time = time;
        return clock_settime(id, &_time) != -1;
    }
    
}
