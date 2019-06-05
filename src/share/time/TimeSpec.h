//
// Created by Khyber on 5/20/2019.
//

#pragma once

#include "src/share/io/fs.h"

#include <time.h>

// time is already a function, so I can't have namespace time
namespace _time {
    
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
        
        constexpr timespec impl() const noexcept {
            return {
                    .tv_sec = seconds,
                    .tv_nsec = nanoseconds,
            };
        }
        
        /*implicit*/ constexpr operator timespec() const noexcept {
            return impl();
        }
        
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
    
    constexpr TimeSpec operator+(const TimeSpec& a, const TimeSpec& b) noexcept {
        return TimeSpec::Args {
                .seconds = a.seconds + b.seconds,
                .nanoseconds = a.nanoseconds + b.nanoseconds,
        };
    }
    
    constexpr TimeSpec operator-(const TimeSpec& a, const TimeSpec& b) noexcept {
        return TimeSpec::Args {
                .seconds = a.seconds - b.seconds,
                .nanoseconds = a.nanoseconds - b.nanoseconds,
        };
    }
    
}
