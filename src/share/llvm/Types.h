//
// Created by Khyber on 2/17/2019.
//

#pragma once

#include <iostream>

#include "src/share/common/numbers.h"

#include "llvm/IR/IRBuilder.h"

namespace llvm {
    
    class Types {
    
    public:
        
        LLVMContext& context;
        
        explicit constexpr Types(LLVMContext& context) noexcept : context(context) {}
        
        template <u32 numBytes>
        IntegerType& integral() const noexcept {
            return *Type::getIntNTy(context, numBytes);
        }
        
        template <u32 numBytes>
        Type& floating() const noexcept {
            llvm_unreachable("Unsupported type");
        }
        
        template <typename T>
        IntegerType& integral() const noexcept {
            static_assert(std::is_integral_v<T>);
            return integral<numBits<T>()>();
        }
        
        template <typename T>
        Type& floating() const noexcept {
            static_assert(std::is_floating_point_v<T>);
            return floating<numBits<T>()>();
        }

    private:

        template <typename T>
        Type& getImpl() const noexcept {
            constexpr bool isIntegral = std::is_integral_v<T>;
            constexpr bool isFloating = std::is_floating_point_v<T>;
            constexpr bool isPointer = std::is_pointer_v<T>;
            constexpr bool isFunction = std::is_function_v<T>;
            static_assert(isIntegral || isFloating || isPointer || isFunction, "Unsupported type");
            if constexpr (isIntegral) {
                return integral<T>();
            }
            if constexpr (isFloating) {
                return floating<T>();
            }
            if constexpr (isPointer) {
                return *get<std::remove_pointer_t<T>>().getPointerTo();
            }
            if constexpr (isFunction) {
                return func<T>();
            }
            llvm_unreachable("Unsupported type");
        }
        
    public:
        
        template <typename T>
        Type& get() const noexcept {
            return getImpl<std::remove_cv_t<T>>();
        }
        
        template <typename... Types>
        auto convert() const noexcept {
            return SmallVector<Type*, sizeof...(Types)> {&get<Types>()...};
        }

    private:
    
        template <typename Return, typename... Args>
        FunctionType& rawFunction(bool isVarArg) const {
            // FunctionType doesn't need to hold memory for args/params; it copies them in some way
            auto args = new SmallVector<Type*, sizeof...(Args)>(convert<Args...>());
            return *FunctionType::get(&get<Return>(), *args, isVarArg);
        }
        
        template <class F>
        struct Function;
    
        // TODO other function type variants (noexcept, ref, cv-qualified) if needed
        
        template <typename Return, typename... Args>
        struct Function<Return(Args...)> {
            
            const Types& types;
            
            FunctionType& operator()() const {
                return types.rawFunction<Return, Args...>(false);
            }
            
        };
    
        template <typename Return, typename... Args>
        struct Function<Return(Args... , ...)> {
        
            const Types& types;
        
            FunctionType& operator()() const {
                return types.rawFunction<Return, Args...>(true);
            }
        
        };

    public:
        
        template <class F>
        FunctionType& func() const {
            return Function<F> {*this}();
        }
        
        ArrayType& array(Type& type, u64 numElements) const {
            return *ArrayType::get(&type, numElements);
        }
        
        template <typename T>
        ArrayType& array(u64 numElements) const {
            return array(get<T>(), numElements);
        }
        
    };
    
    #define specialize template <> inline
    
    #define _(T) *Type::get##T##Ty(context)
    
    #define makeIntegral(numBytes) \
    specialize IntegerType& Types::integral<numBytes>() const noexcept { \
        return _(Int##numBytes); \
    }
    
    makeIntegral(1)
    makeIntegral(8)
    makeIntegral(16)
    makeIntegral(32)
    makeIntegral(64)
    makeIntegral(128)
    
    #undef makeIntegral
    
    #define makeFloating(numBytes, name) \
    specialize Type& Types::floating<numBytes>() const noexcept { \
        return _(name); \
    }
    
    makeFloating(16, Half)
    makeFloating(32, Float)
    makeFloating(64, Double)
    makeFloating(128, FP128)
    makeFloating(80, X86_FP80)

    #undef makeFloating
    
    specialize Type& Types::getImpl<void>() const noexcept {
        return _(Void);
    }
    
    #undef _
    
    // LLVM has no void*, so use u8/i8* instead
    #define makeVoidPtr(cv) \
    specialize Type& Types::getImpl<cv void*>() const noexcept { \
        return get<u8*>(); \
    }
    
    makeVoidPtr()
    makeVoidPtr(const)
    makeVoidPtr(volatile)
    makeVoidPtr(const volatile)
    
    #undef specialize
    
}
