//
// Created by Khyber on 6/4/2019.
//

#include "src/share/capability/prctl.h"

namespace capability {
    
    // ::prctl is untyped (variadic) but requires long arguments
    
    namespace _ {
        
        int prctl(int option, u64 a) noexcept {
            return ::prctl(option, a);
        }
        
        int prctl(int option, u64 a, u64 b) noexcept {
            return ::prctl(option, a, b);
        }
        
    }
    
    #define $(x) static_cast<u64>(x)
    
    int prctl(BoundOption option, Capability capability) noexcept {
        return _::prctl($(option), $(capability));
    }
    
    int prctl(AmbientFlag, AmbientOption ambientOption, Capability capability) noexcept {
        return _::prctl($(AmbientFlag::single), $(ambientOption), $(capability));
    }
    
    int prctl(AmbientClear) noexcept {
        return _::prctl($(AmbientFlag::single), $(AmbientClear::all), 0);
    }
    
    #undef $
    
}
