//
// Created by Khyber on 2/17/2019.
//

#pragma once

#include <iostream>

#include "llvm/IR/IRBuilder.h"
#include "numbers.h"
#include "debug.h"

namespace llvm {
    
    class Types {
    
    public:
        
        LLVMContext& context;
        
        explicit constexpr Types(LLVMContext& context) noexcept : context(context) {}
        
        template <u32 numBytes>
        IntegerType* integral() const noexcept {
            return Type::getIntNTy(context, numBytes);
        }
        
        template <u32 numBytes>
        Type* floating() const noexcept {
            llvm_unreachable("Unsupported type");
        }
        
        template <typename T>
        IntegerType* integral() const noexcept {
            static_assert(std::is_integral_v<T>);
            return integral<std::numeric_limits<T>::digits>();
        }
        
        template <typename T>
        Type* floating() const noexcept {
            static_assert(std::is_floating_point_v<T>);
            return floating<std::numeric_limits<T>::digits>();
        }
        
        template <typename T>
        Type* get() const noexcept {
            constexpr bool isIntegral = std::is_integral_v<T>;
            constexpr bool isFloating = std::is_floating_point_v<T>;
            constexpr bool isPointer = std::is_pointer_v<T>;
            static_assert(isIntegral || isFloating || isPointer, "Unsupported type");
            if constexpr (isIntegral) {
                return integral<T>();
            } else if constexpr (isFloating) {
                return floating<T>();
            } else if constexpr (isPointer) {
                return get<std::remove_pointer_t<T>>();
            } else {
                llvm_unreachable("Unsupported type");
            }
        }
        
        template <typename... Types>
        auto convert() const noexcept {
            return SmallVector<Type*, sizeof...(Types)> {get<Types>()...};
        }
        
        template <typename Return, typename... Args>
        FunctionType* function(bool isVarArg = false) const noexcept {
            // FunctionType doesn't need to hold memory for args/params; it copies them in some way
            return FunctionType::get(get<Return>(), convert<Args...>(), isVarArg);
        }
        
    };
    
    
    template <>
    IntegerType* Types::integral<1>() const noexcept {
        return Type::getInt1Ty(context);
    }
    
    template <>
    IntegerType* Types::integral<8>() const noexcept {
        return Type::getInt8Ty(context);
    }
    
    template <>
    IntegerType* Types::integral<16>() const noexcept {
        return Type::getInt16Ty(context);
    }
    
    template <>
    IntegerType* Types::integral<32>() const noexcept {
        std::cout << "32" << std::endl;
        return Type::getInt32Ty(context);
    }
    
    template <>
    IntegerType* Types::integral<64>() const noexcept {
        return Type::getInt64Ty(context);
    }
    
    template <>
    IntegerType* Types::integral<128>() const noexcept {
        return Type::getInt128Ty(context);
    }
    
    
    template <>
    Type* Types::floating<16>() const noexcept {
        return Type::getHalfTy(context);
    };
    
    template <>
    Type* Types::floating<32>() const noexcept {
        return Type::getFloatTy(context);
    };
    
    template <>
    Type* Types::floating<64>() const noexcept {
        return Type::getDoubleTy(context);
    };
    
    template <>
    Type* Types::floating<128>() const noexcept {
        return Type::getFP128Ty(context);
    };
    
    template <>
    Type* Types::floating<80>() const noexcept {
        return Type::getX86_FP80Ty(context);
    };
    
    
    template <>
    Type* Types::get<void>() const noexcept {
        return Type::getVoidTy(context);
    };
    
}
