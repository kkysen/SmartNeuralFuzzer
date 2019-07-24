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
        constexpr ConstantInt& getInt(T t) const {
            return *ConstantInt::get(&types.integral<T>(), t, std::is_signed_v<T>);
        }
        
        // ConstantDataArray::get does the same thing,
        // but it uses Type::getScalarTy<T>(), which is a much less powerful types.get<T>().
        template <typename T>
        constexpr ConstantDataArray& dataArray(ArrayRef<T> array) const {
            const auto data = reinterpret_cast<const char*>(array.data());
            const auto string = StringRef(data, array.size() * sizeof(T));
            return *ConstantDataArray::getRaw(string, array.size(), types.get<T>());
        }
        
        template <typename T>
        constexpr UndefValue& undefined() const {
            return *UndefValue::get(&types.get<T>());
        }
        
    };
    
}
