//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/hook/lifecycle/signaling/signaling.h"

#include "src/share/aio/signal/handler/AltStack.h"
#include "src/share/aio/signal/handler/Func.h"

#include "llvm/ADT/SmallVector.h"

namespace aio::signal::handler {
    
    /**
     * This is a passive handler because it only registers for signals
     * that don't have an existing handler and have a default disposition that crashes the program.
     * This handler's job is to prevent the program from crashing due to a signal.
     * It has support from hook::libc to re-register for a signal
     * if a signal handler is removed from that signal.
     *
     * It also keeps a special signal, hook::lifecycle::signaling::constants::signal, completely open.
     * That is, it behaves like the Resilient handler in this case,
     * only running the user's signal handler after this one.
     */
    class Passive {
    
        AltStack altStack;
        llvm::SmallVector<HandlerFunc, 2> handlers;
    
    };
    
}
