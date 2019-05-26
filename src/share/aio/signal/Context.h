//
// Created by Khyber on 5/25/2019.
//

#pragma once

#include <csignal>

namespace aio::signal {
    
    struct ConstContext {
        
        const ucontext_t& impl;
        
        /*implicit*/ constexpr ConstContext(const ucontext_t& impl) noexcept : impl(impl) {}
        
        /*implicit*/ constexpr operator const ucontext_t&() const noexcept {
            return impl;
        }
        
        constexpr const ucontext_t& linkRaw() const noexcept {
            return *impl.uc_link;
        };
        
        constexpr ConstContext link() const noexcept {
            return linkRaw();
        }
        
        #define field(T, name, implName) \
        constexpr const T& name() const noexcept { \
            return impl.implName; \
        } \

        #define fields() \
        field(sigset_t, mask, uc_sigmask) \
        field(stack_t, stack, uc_stack) \
        field(mcontext_t, machineContext, uc_mcontext) \

        
        fields()
        
        #undef field
        
    };

// impl dependent, so need to wrap impl ptr
    struct Context {
        
        ucontext_t& impl;
        
        /*implicit*/ constexpr Context(ucontext_t& impl) noexcept : impl(impl) {}
        
        /*implicit*/ constexpr operator ucontext_t&() noexcept {
            return impl;
        }
        
        constexpr const ucontext_t& linkRaw() const noexcept {
            return *impl.uc_link;
        };
        
        constexpr ucontext_t& linkRaw() noexcept {
            return *impl.uc_link;
        }
        
        constexpr ConstContext link() const noexcept {
            return linkRaw();
        }
        
        constexpr Context link() noexcept {
            return linkRaw();
        }
        
        #define field(T, name, implName) \
        constexpr const T& name() const noexcept { \
            return impl.implName; \
        } \
        constexpr T& name() noexcept { \
            return impl.implName; \
        } \

        
        fields()
        
        #undef field
        #undef fields
        
    };
    
}
