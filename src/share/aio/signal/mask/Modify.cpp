//
// Created by Khyber on 5/30/2019.
//

#include "src/share/aio/signal/mask/Modify.h"

namespace aio::signal::mask {
    
    bool Modify::operator()(sigset_t& set, int signal) const noexcept {
        return raw()(&set, signal) == 0;
    }
    
}
