//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/BitCached.h"

namespace capability {
    
    template <Capability capability>
    class Ambient : public BitCached<Ambient, capability> {

    private:
    
        using Super = BitCached<Ambient, capability>;
        using Super::cache;
        
        static int call(AmbientOption option) noexcept {
            return prctl(AmbientFlag::single, option, capability);
        }

    public:
    
        bool get() const noexcept {
            if (cache.use && cache.is) {
                return cache.value;
            }
            // won't set EINVAL (only error) b/c I know capability is valid
            return cache = (call(AmbientOption::IS) == 1);
        }
    
        // returns false if error
        bool set(const bool value) noexcept {
            const bool succeeded = call(value ? AmbientOption::RAISE : AmbientOption::LOWER) == 0;
            if (succeeded) {
                cache = false;
            }
            return succeeded;
        }
        
        bool operator=(bool value) noexcept {
            return set(value);
        }
    
    };
    
}
