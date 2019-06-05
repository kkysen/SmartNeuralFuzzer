//
// Created by Khyber on 6/4/2019.
//

#include "src/share/aio/signal/HandlerConst.h"

#include <cassert>

namespace aio::signal {
    
    bool HandlerConst::check() noexcept {
        const bool _checked = HandlerConst(error) == SIG_ERR
                              && HandlerConst(default_) == SIG_DFL
                              && HandlerConst(ignore) == SIG_IGN
                              && HandlerConst(hold) == SIG_HOLD;
        assert(_checked);
        return _checked;
    }
    
    const bool HandlerConst::checked = check();
    
    HandlerConst::HandlerConst(sighandler_t handler) noexcept
            : raw(static_cast<Raw>(reinterpret_cast<intptr_t>(handler))) {}
    
    HandlerConst::operator sighandler_t() noexcept {
        return reinterpret_cast<sighandler_t>(static_cast<intptr_t>(raw));
    }
    
}
