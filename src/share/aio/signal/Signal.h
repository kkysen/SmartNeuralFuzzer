//
// Created by Khyber on 5/24/2019.
//

#pragma once


#include "src/share/aio/signal/Info.h"
#include "src/share/aio/signal/Context.h"
#include "src/share/aio/signal/Disposition.h"

namespace aio::signal {
    
    class Signal {
    
    public:
        
        int signal;
        const Info& info;
        ConstContext context;
        const disposition::Default& defaultDisposition;
        
        constexpr Signal(int signal, const Info& info, ConstContext context) noexcept
                : signal(signal), info(info), context(context),
                  defaultDisposition(*disposition::getDefault(signal)) {}
        
        // could be constexpr, see Info::of()
        Signal(int signal, const siginfo_t* sigInfo, const void* context) noexcept;
        
    };
    
}