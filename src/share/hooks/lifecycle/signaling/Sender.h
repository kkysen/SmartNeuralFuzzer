//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include "src/share/hooks/lifecycle/signaling/signaling.h"

namespace hooks::lifecycle::signaling {
    
    class Sender {
    
    private:
        
        Info info = Info::value(constants::code, Value::of::val(constants::magicNumber));
    
    public:
        
        Sender() noexcept = default;
        
        void operator()(pid_t tid);
        
    };
    
}
