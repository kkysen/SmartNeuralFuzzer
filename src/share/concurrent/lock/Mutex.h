//
// Created by Khyber on 5/31/2019.
//

#pragma once

#include <mutex>

namespace concurrent {
    
    namespace mutex {
        
        class Init {
        
        public:
            
            enum Type {
                
                _default,
                
                #ifdef PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP
                recursive,
                #endif
                
                #ifdef PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP
                errorCheck,
                #endif
                
                #ifdef PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP
                adaptive,
                #endif
                
            };
        
        private:
            
            struct Raw {
                
                static constexpr pthread_mutex_t _default = PTHREAD_MUTEX_INITIALIZER;
                
                #ifdef PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP
                static constexpr pthread_mutex_t recursive = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
                #endif
                
                #ifdef PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP
                static constexpr pthread_mutex_t errorCheck = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
                #endif
                
                #ifdef PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP
                static constexpr pthread_mutex_t adaptive = PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP;
                #endif
                
            };
            
            Type type;
        
        public:
            
            /*implicit*/ constexpr Init(Type type) noexcept : type(type) {}
            
            constexpr const pthread_mutex_t& raw() const noexcept {
                switch (type) {
                    case _default:
                        return Raw::_default;
                    case recursive:
                        return Raw::recursive;
                    case errorCheck:
                        return Raw::errorCheck;
                    case adaptive:
                        return Raw::adaptive;
                }
            }
            
        };
        
    }
    
    // wraps std::mutex, but allows for different initializers
    template <mutex::Init::Type init = mutex::Init::_default>
    class Mutex {
    
    private:
        
        std::mutex mutex;
    
    public:
        
        constexpr const std::mutex& impl() const noexcept {
            return mutex;
        }
        
        constexpr std::mutex& impl() noexcept {
            return mutex;
        }
        
        constexpr auto native_handle() noexcept {
            return mutex.native_handle();
        }
        
        constexpr Mutex() noexcept {
            *mutex.native_handle() = mutex::Init(init).raw();
        }
        
        void unlock() noexcept {
            mutex.unlock();
        }
        
        bool tryLock() noexcept {
            return mutex.try_lock();
        }
        
        bool try_lock() noexcept {
            return tryLock();
        }
        
        void lock() noexcept {
            mutex.lock();
        }
        
    };
    
}
