//
// Created by Khyber on 5/30/2019.
//

#include "src/share/aio/signal/mask/Masker.h"

namespace aio::signal::mask {
    
    Masker::Masker(const Mask& mask, How how, Apply apply) noexcept
            : mask(mask), old(apply, mask, how), apply(apply) {}
    
    Masker::~Masker() {
        mask.apply(apply, How::set);
    }
    
}
