//
// Created by Khyber on 5/25/2019.
//

#pragma once

#include "src/share/common/numbers.h"

#include <array>

#include <csignal>

namespace aio::signal::disposition {
    
        enum class Disposition {
            terminate,
            ignore,
            coreDump,
            stop,
            resume,
            unstoppable,
        };
    
        struct Default {
        
            const int signal;
            const Disposition disposition;
        
            const bool isUnstoppable;
            const bool onlyTerminates;
            const bool dumpsCore;
            const bool terminates; // onlyTerminates or dumpsCore
            const bool stops;
            const bool atLeastStops; // includes terminates
            const bool resumes;
            const bool isIgnored;
        
            constexpr Default(int signal, Disposition disposition) noexcept
                    : signal(signal), disposition(disposition),
                      isUnstoppable(disposition == Disposition::unstoppable),
                      onlyTerminates(disposition == Disposition::terminate),
                      dumpsCore(disposition == Disposition::coreDump),
                      terminates(onlyTerminates || dumpsCore),
                      stops(disposition == Disposition::stop),
                      atLeastStops(terminates || stops),
                      resumes(disposition == Disposition::resume),
                      isIgnored(disposition == Disposition::ignore) {}
        
        };
    
        #define _(_signal, _disposition) \
        Default(SIG##_signal, Disposition::_disposition)

        // http://man7.org/linux/man-pages/man7/signal.7.html
        constexpr std::array<Default, 34> defaults = {
                _(ABRT, coreDump),
                _(ALRM, terminate),
                _(BUS, coreDump),
                _(CHLD, ignore),
                _(CLD, ignore),
                _(CONT, resume),
//          _(EMT, terminate),
                _(FPE, coreDump),
                _(HUP, terminate),
                _(ILL, coreDump),
//          _(INFO, terminate),
                _(INT, terminate),
                _(IO, terminate),
                _(IOT, coreDump),
                _(KILL, unstoppable), // terminate
//          _(LOST, terminate),
                _(PIPE, terminate),
                _(POLL, terminate),
                _(PROF, terminate),
                _(PWR, terminate),
                _(QUIT, coreDump),
                _(SEGV, coreDump),
                _(STKFLT, terminate),
                _(STOP, unstoppable), // stop
                _(TSTP, stop),
                _(SYS, coreDump),
                _(TERM, terminate),
                _(TRAP, coreDump),
                _(TTIN, stop),
                _(TTOU, stop),
//          _(UNUSED, coreDump),
                _(URG, ignore),
                _(USR1, terminate),
                _(USR1, terminate),
                _(VTALRM, terminate),
                _(XCPU, coreDump),
                _(XFSZ, coreDump),
                _(WINCH, ignore),
        };
    
        #undef _
        
        constexpr const Default* getDefault(int signal) noexcept {
            for (const auto& disposition : defaults) {
                if (disposition.signal == signal) {
                    return &disposition;
                }
            }
            return nullptr;
        }
        
    }
