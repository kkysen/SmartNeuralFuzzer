//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include "src/share/llvm/Types.h"

#include "llvm/IR/Module.h"

#include <string_view>

namespace llvm {
    
    class Api {
    
    public:
        
        const std::string_view name;
    
    private:
        
        Module& module;
        Types types;
    
    public:
        
        constexpr Api(std::string_view name, Module& module) noexcept
                : name(name), module(module), types(module.getContext()) {}
        
        template <typename... Args>
        FunctionCallee func(std::string_view funcName) const {
            std::string fullName = "__";
            fullName += name;
            fullName += "_";
            fullName += funcName;
            auto x = types.function<void, Args...>();
            llvm_dbg(x->getReturnType());
            Function *f = Function::Create(x, GlobalVariable::ExternalLinkage,
                                           module.getDataLayout().getProgramAddressSpace(), fullName, &module);
            module.getFunctionList().push_back(f);
//            auto y = module.getOrInsertFunction(fullName, x);
            FunctionCallee y = {x, f};
            llvm_dbg(y.getFunctionType()->getReturnType());
            return y;
        }
        
    };
    
}
