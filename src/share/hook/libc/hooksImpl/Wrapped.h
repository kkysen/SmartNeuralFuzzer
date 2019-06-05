//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include <memory>

namespace hook::libc {
    
    template <typename R, void inside()>
    class Wrapped {
    
    public:
        
        using F = R(*)(void*);
    
    private:
        
        class Arg {
            
            const F f;
            void* const arg;
        
        public:
            
            constexpr Arg(F f, void* arg) noexcept : f(f), arg(arg) {}
            
            R operator()() {
                return f(arg);
            }
            
        };
        
        std::unique_ptr<Arg> _arg;
    
    public:
        
        const F f = [](void* arg) {
            inside();
            return (*reinterpret_cast<Arg*>(arg))();
        };
        
        constexpr Wrapped(F f, void* arg) : _arg(std::make_unique<Arg>(f, arg)) {}
        
        constexpr Arg* arg() const noexcept {
            return &*_arg;
        }
        
    };
    
}
