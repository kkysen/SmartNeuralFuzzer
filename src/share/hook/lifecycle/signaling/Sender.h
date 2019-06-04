//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include "src/share/hook/lifecycle/signaling/signaling.h"

namespace hook::lifecycle::signaling {
    
    class Sender {
    
    private:
        
        Info info = Info::value(constants::code, Value::of::val(constants::magicNumber));
    
    public:
        
        Sender() noexcept = default;
        
        void operator()(pid_t tid);
        
    };
    
}
