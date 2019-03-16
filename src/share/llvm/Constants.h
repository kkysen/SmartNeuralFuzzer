//
// Created by Khyber on 2/17/2019.
//

#pragma once

#include "src/share/llvm/Types.h"

namespace llvm {
    
    class Constants {
    
    private:
        
        const Types types;
    
    public:
        
        explicit constexpr Constants(LLVMContext& context) : types(context) {}
        
        template <typename T>
        constexpr ConstantInt* getInt(T t) const {
            return ConstantInt::get(types.integral<T>(), t, std::is_signed_v<T>);
        }
        
    };
    
}
