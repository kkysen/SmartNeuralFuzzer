//
// Created by Khyber on 6/4/2019.
//

#include "src/share/capability/Data.h"

namespace capability {
    
    const Data::Impl& Data::impl() const noexcept {
        return reinterpret_cast<const Impl&>(*this);
    }
    
    Data::Impl& Data::impl() noexcept {
        return reinterpret_cast<Impl&>(*this);
    }
    
    Data::operator const Impl&() const noexcept {
        return impl();
    }
    
    Data::operator Impl&() noexcept {
        return impl();
    }
    
}
