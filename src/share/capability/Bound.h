//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/BitCached.h"

namespace capability {
    
    template <Capability capability>
    class Bound : public BitCached<Bound, capability> {

    private:

        using Super = BitCached<Bound, capability>;
        using Super::cache;

    public:
        
        bool get() const noexcept {
            if (cache.use && cache.is) {
                return cache.value;
            }
            // won't set EINVAL (only error) b/c I know capability is valid
            return cache = (prctl(BoundOption::read, capability) == 1);
        }
        
        // returns false if error
        bool drop() noexcept {
            const bool succeeded = prctl(BoundOption::drop, capability) == 0;
            if (succeeded) {
                cache = false;
            }
            return succeeded;
        }
        
        bool operator=(std::nullptr_t) noexcept {
            return drop();
        }
    
    };
    
}
