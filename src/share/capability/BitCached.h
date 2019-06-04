//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/BitCache.h"
#include "src/share/capability/Capability.h"
#include "src/share/capability/prctl.h"

namespace capability {
    
    using capability::prctl;
    
    template <template <Capability capability> class _Base, Capability capability>
    class BitCached {

    private:
        
        using Base = _Base<capability>;
        
        constexpr Base& base() noexcept {
            return static_cast<Base&>(*this);
        }
        
    protected:
        
        BitCache cache;
    
    public:
        
        constexpr Base& useCache(bool _cache = true) noexcept {
            cache.use = _cache;
            return base();
        }
        
        constexpr Base& resetCache() noexcept {
            cache.is = false;
            return base();
        }
    
        explicit operator bool() const noexcept {
            return Base::get();
        }
        
    };
    
}

