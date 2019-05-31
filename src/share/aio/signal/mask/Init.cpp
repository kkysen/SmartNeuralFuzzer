//
// Created by Khyber on 5/30/2019.
//

#include "src/share/aio/signal/mask/Init.h"

namespace aio::signal::mask {
    
    void Init::operator()(sigset_t& set) const noexcept {
        raw()(&set);
    }
    
}
