//
// Created by Khyber on 5/30/2019.
//

#include "src/share/aio/signal/mask/Apply.h"

namespace aio::signal::mask {
    
    bool Apply::operator()(How how, const sigset_t* set, sigset_t* old) const noexcept {
        return raw()(static_cast<int>(how), set, old) == 0;
    }
    
    bool Apply::operator()(How how, const sigset_t& set, sigset_t& old) const noexcept {
        return (*this)(how, &set, &old);
    }
    
    bool Apply::operator()(How how, const sigset_t& set) const noexcept {
        return (*this)(how, &set, nullptr);
    }
    
}
