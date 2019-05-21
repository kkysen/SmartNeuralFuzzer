//
// Created by Khyber on 5/20/2019.
//

#pragma once

#include <time.h>

// TODO this shouldn't really go in io, right?
namespace io {
    
    struct TimeSpec {
        
        struct Args {
            time_t seconds;
            long nanoseconds;
        };
        
        time_t seconds;
        long nanoseconds;
        
        /*implicit*/ constexpr TimeSpec(Args args) noexcept : seconds(args.seconds), nanoseconds(args.nanoseconds) {}
        
        constexpr TimeSpec(time_t seconds, long nanoseconds) noexcept
                : TimeSpec(Args {.seconds = seconds, .nanoseconds = nanoseconds}) {}
        
        /*implicit*/ constexpr TimeSpec(timespec timespec) noexcept
                : TimeSpec(Args {.seconds = timespec.tv_sec, .nanoseconds = timespec.tv_nsec}) {}
        
        // TODO other related functions
        
    };
    
    constexpr bool operator==(const TimeSpec& a, const TimeSpec& b) noexcept {
        return a.seconds == b.seconds && a.nanoseconds == b.nanoseconds;
    }
    
    constexpr bool operator!=(const TimeSpec& a, const TimeSpec& b) noexcept {
        return !(a == b);
    }
    
    constexpr bool operator<(const TimeSpec& a, const TimeSpec& b) noexcept {
        return a.seconds < b.seconds && a.nanoseconds < b.nanoseconds;
    }
    
    constexpr bool operator>(const TimeSpec& a, const TimeSpec& b) noexcept {
        return b < a;
    }
    
    constexpr bool operator<=(const TimeSpec& a, const TimeSpec& b) noexcept {
        return !(a > b);
    }
    
    constexpr bool operator>=(const TimeSpec& a, const TimeSpec& b) noexcept {
        return !(a < b);
    }
    
}
