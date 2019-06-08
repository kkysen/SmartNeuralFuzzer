//
// Created by Khyber on 5/26/2019.
//

#include "src/share/aio/signal/handler/AltStack.h"

#include "src/share/common/hardAssert.h"

namespace aio::signal::handler {
    
    bool AltStack::register_(int flags) const noexcept {
        const stack_t ss = {
                .ss_sp = stack.data(),
                .ss_size = stack.size(),
                .ss_flags = flags,
        };
        return ::sigaltstack(&ss, nullptr) == 0;
    }
    
    // https://github.com/torvalds/linux/blob/master/include/uapi/linux/signal.h
    #ifndef SS_AUTODISARM
    #define SS_AUTODISARM static_cast<int>(1u << 31u)
    #endif
    
    bool AltStack::register_() const noexcept {
        if (register_(SS_AUTODISARM)) {
            return true;
        }
        // kernel doesn't support autodisarm if errno == EINVAL
        if (errno == EINVAL && register_(0)) {
            return true;
        }
        /**
         * Only EPERM is possible
         *
         * EFAULT: ss or old_ss are non-null and outside of the process address space
         *      ss is in the address space and old_ss is nullptr
         * ENOMEM: ss_size is not < MINSIGSTKSZ b/c static_assert(size >= MINSIGSTKSZ)
         * EPERM: currently executing on sig alt stack
         */
        hardAssert(errno == EPERM);
        return false;
    }
    
    AltStack::AltStack() noexcept {
        if (register_()) {
            _registered = true;
        }
    }
    
}
