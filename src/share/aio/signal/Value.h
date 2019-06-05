//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include "src/share/common/numbers.h"

#include <csignal>

namespace aio::signal {
    
    class Value {
    
    public:
        
        union Raw {
            u64 val;
            void* ptr;
        } raw;
    
    private:
        
        explicit constexpr Value(Raw raw) noexcept : raw(raw) {}
    
    public:
        
        /*implicit*/ constexpr Value(sigval_t value) noexcept : Value({.ptr = value.sival_ptr}) {}
        
        /*implicit*/ constexpr operator sigval_t() noexcept {
            return {.sival_ptr = raw.ptr};
        }
        
        template <typename T>
        explicit constexpr Value(T t) noexcept : raw({.val = static_cast<u64>(t)}) {
            static_assert(sizeof(t) <= sizeof(raw.val));
        }
        
        template <typename T>
        constexpr T val() const noexcept {
            static_assert(sizeof(T) <= sizeof(raw.val));
            return static_cast<T>(raw.val);
        }
        
        template <typename T>
        constexpr const T* ptr() const noexcept {
            return static_cast<const T*>(raw.ptr);
        }
        
        template <typename T>
        constexpr T* ptr() noexcept {
            return static_cast<T*>(raw.ptr);
        }
        
        template <typename T>
        constexpr const T& ref() const noexcept {
            return *ptr<T>();
        }
        
        template <typename T>
        constexpr T& ref() noexcept {
            return *ptr<T>();
        }
        
        template <typename T>
        constexpr auto get() const noexcept {
            if constexpr (sizeof(T) <= sizeof(raw.val)) {
                return val<T>();
            } else {
                return ref<T>();
            }
        }
        
        template <typename T>
        constexpr auto get() noexcept {
            if constexpr (sizeof(T) <= sizeof(raw.val)) {
                return val<T>();
            } else {
                return ref<T>();
            }
        }
        
        template <typename T>
        constexpr auto operator()() const noexcept {
            return get<T>();
        }
        
        template <typename T>
        constexpr auto operator()() noexcept {
            return get<T>();
        }
        
        template <typename T>
        constexpr bool operator==(const T& t) const noexcept {
            return get<T>() == t;
        }
        
        template <typename T>
        constexpr bool operator!=(const T& t) const noexcept {
            return !((*this) == t);
        }
        
        struct of {
            
            template <typename T>
            static constexpr Value val(T t) noexcept {
                static_assert(sizeof(t) <= sizeof(Raw));
                return Value({.val = static_cast<u64>(t)});
            }
            
            template <typename T>
            static constexpr Value ptr(const T& t) noexcept {
                return Value({.ptr = &t});
            }
            
        };
        
    };
    
}
