//
// Created by Khyber on 5/23/2019.
//

#include "SignalHandler.h"

namespace {
    
    using namespace aio;
    
    SignalHandlerFunc convert(RawSigActionHandler handler) {
        return [handler](const Signal& signal) {
            const siginfo_t& sigInfo = signal.info;
            const ucontext_t& context = signal.context;
            // TODO why is this casting to an incompatible type?
            // this is just a const_cast
            auto& mutSigInfo = const_cast<siginfo_t&>(sigInfo);
            auto& mutContext = const_cast<ucontext_t&>(context);
            siginfo_t* sigInfoPtr = &mutSigInfo;
            void* contextPtr = &mutContext;
            handler(signal.signal, sigInfoPtr, contextPtr);
        };
    }
    
    SignalHandlerFunc convert(RawSignalHandler handler) {
        return [handler](const Signal& signal) {
            handler(signal.signal);
        };
    }
    
    SignalHandlerFunc convert(struct sigaction action) {
        if (action.sa_flags & SA_SIGINFO) {
            return convert(action.sa_sigaction);
        } else {
            const auto handler = action.sa_handler;
            if (handler == SIG_DFL || handler == SIG_IGN) {
                return nullptr;
            } else {
                return convert(handler);
            }
        }
    }
    
}

namespace aio {
    
    void SignalHandler::add(SignalHandlerFunc&& handler, size_t index) {
        if (handler) {
            handlers.insert(handlers.begin() + index, std::move(handler));
        }
    }
    
    void SignalHandler::add(struct sigaction action, size_t index) {
        add(convert(action), index);
    }
    
    void SignalHandler::add(SignalHandlerFunc&& handler) {
        return add(std::move(handler), size());
    }
    
    void SignalHandler::add(struct sigaction action) {
        return add(action, size());
    }
    
    void SignalHandler::addExisting(struct sigaction action) {
        add(action, 0);
    }
    
    bool SignalHandler::registerSigAltStack(int flags) const noexcept {
        const stack_t ss = {
                .ss_sp = alternateStack.data(),
                .ss_size = alternateStack.size(),
                .ss_flags = flags,
        };
        return sigaltstack(&ss, nullptr) == 0;
    }
    
    // https://github.com/torvalds/linux/blob/master/include/uapi/linux/signal.h
    #ifndef SS_AUTODISARM
    #define SS_AUTODISARM static_cast<int>(1u << 31u)
    #endif
    
    bool SignalHandler::registerSigAltStack() const noexcept {
        if (registerSigAltStack(SS_AUTODISARM)) {
            return true;
        }
        // kernel doesn't support autodisarm if errno == EINVAL
        if (errno == EINVAL && registerSigAltStack(0)) {
            return true;
        }
        /**
         * Only EPERM is possible
         *
         * EFAULT: ss or old_ss are non-null and outside of the process address space
         *      ss is in the address space and old_ss is nullptr
         * ENOMEM: ss_size is not < MINSIGSTKSZ b/c static_assert(SIGSTKSZ >= MINSIGSTKSZ)
         * EPERM: currently executing on sig alt stack
         */
        assert(errno == EPERM);
        return false;
    }
    
}
