//
// Created by Khyber on 2/17/2019.
//

#pragma once

#include "llvm/IR/IRBuilder.h"
#include "Types.h"
#include "Constants.h"

namespace llvm {
    
    class IRBuilderExt {
    
    public:
        
        IRBuilder<>& builder;
        
        explicit constexpr IRBuilderExt(IRBuilder<>& builder) : builder(builder) {}
        
        template <typename T>
        static constexpr T* mut(const T* value) noexcept {
            return const_cast<T*>(value);
        }
        
        constexpr LLVMContext& context() const noexcept {
            return builder.getContext();
        }
        
        constexpr Types types() const noexcept {
            return Types(context());
        }
        
        constexpr Constants constants() const noexcept {
            return Constants(context());
        }
        
        constexpr CallInst* call(FunctionCallee callee, ArrayRef<Value*> args = None,
                                 const Twine& name = "", MDNode* floatingPointMathTag = nullptr) const {
            return builder.CreateCall(callee, args, name, floatingPointMathTag);
        }
        
    };
    
}

