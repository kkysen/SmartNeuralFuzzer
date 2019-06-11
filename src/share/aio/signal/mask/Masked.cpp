//
// Created by Khyber on 5/30/2019.
//

#include "src/share/aio/signal/mask/Masked.h"

namespace aio::signal::mask {
    
    Masked::Masked(const Mask& mask, How how, Apply apply) noexcept
            : mask(mask), old(apply, mask, how), apply(apply) {}
    
    Masked::~Masked() {
        mask.apply(apply, How::set);
    }
    
}
