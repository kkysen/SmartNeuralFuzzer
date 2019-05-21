//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include "src/share/llvm/Types.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/DerivedTypes.h"

#include <string_view>

namespace llvm {
    
    class Api {
    
    public:
        
        const std::string_view name;
    
    private:
        
        Module& module;
        const Types types;
    
    public:
        
        constexpr Api(std::string_view name, Module& module) noexcept
                : name(name), module(module), types(module.getContext()) {}
        
        template <typename... Args>
        FunctionCallee func(std::string_view funcName) const {
            using namespace std::string_literals;
            return module.getOrInsertFunction((("__"s += name) += "_") += funcName,
                                              types.function<void, Args...>());
        }
        
    };
    
}
