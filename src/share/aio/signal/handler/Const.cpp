//
// Created by Khyber on 6/4/2019.
//

#include "src/share/aio/signal/handler/Const.h"

#include <cassert>

namespace aio::signal::handler {
    
    bool Const::check() noexcept {
        const bool _checked = Const(error) == SIG_ERR
                              && Const(default_) == SIG_DFL
                              && Const(ignore) == SIG_IGN
                              && Const(hold) == SIG_HOLD;
        assert(_checked);
        return _checked;
    }
    
    const bool Const::checked = check();
    
    Const::Const(sighandler_t handler) noexcept
            : raw(static_cast<Raw>(reinterpret_cast<intptr_t>(handler))) {}
    
    Const::operator sighandler_t() noexcept {
        return reinterpret_cast<sighandler_t>(static_cast<intptr_t>(raw));
    }
    
}
