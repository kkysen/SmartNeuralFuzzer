//
// Created by Khyber on 2/17/2019.
//

#pragma once

#include "src/share/llvm/IRBuilderExt.h"

namespace llvm {
    
    class AllocaArgs : public IRBuilderExt {
    
    public:
        
        const Type* type;
        const Value* size;
        
        constexpr AllocaArgs(IRBuilder<>& builder, const Type* type, const Value* size) noexcept
                : IRBuilderExt(builder), type(type), size(size) {}
        
        constexpr AllocaArgs(IRBuilder<>& builder, const Type* type, u64 size) noexcept
                : IRBuilderExt(builder), type(type), size(constants().getInt(size)) {}
    
    private:
        
        template <typename T>
        constexpr AllocaArgs(IRBuilder<>& builder, const Value* size, T) noexcept
                : AllocaArgs(builder, types().get<T>(), size) {}
        
        template <typename T>
        constexpr AllocaArgs(IRBuilder<>& builder, u64 size, T) noexcept
                : AllocaArgs(builder, types().get<T>(), size) {}
    
    public:
        
        template <typename T>
        static constexpr AllocaArgs of(IRBuilder<>& builder, const Value* size) noexcept {
            return AllocaArgs(builder, size, T());
        }
        
        template <typename T>
        static constexpr AllocaArgs of(IRBuilder<>& builder, u64 size) noexcept {
            return AllocaArgs(builder, size, T());
        }
        
        constexpr AllocaInst* operator()() {
            return builder.CreateAlloca(mut(type), mut(size));
        }
        
    };
    
}
