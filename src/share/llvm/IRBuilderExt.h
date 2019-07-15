//
// Created by Khyber on 2/17/2019.
//

#pragma once

#include "src/share/llvm/Types.h"
#include "src/share/llvm/Constants.h"

#include "llvm/IR/IRBuilder.h"

namespace llvm {
    
    class IRBuilderExt {
    
    public:
        
        IRBuilder<>& irb;
        
        explicit constexpr IRBuilderExt(IRBuilder<>& builder) : irb(builder) {}
        
        template <typename T>
        static constexpr T* mut(const T* value) noexcept {
            return const_cast<T*>(value);
        }
        
        constexpr LLVMContext& context() const noexcept {
            return irb.getContext();
        }
        
        constexpr Types types() const noexcept {
            return Types(context());
        }
        
        constexpr Constants constants() const noexcept {
            return Constants(context());
        }
        
        constexpr CallInst& call(FunctionCallee callee, ArrayRef<Value*> args = None,
                                 const Twine& name = "", MDNode* floatingPointMathTag = nullptr) const {
            return *irb.CreateCall(callee, args, name, floatingPointMathTag);
        }
        
        constexpr CallInst& callIndex(FunctionCallee f, u64 index) const {
            return call(f, {&constants().getInt(index)});
        }
        
        template <class InstType>
        constexpr InstType& insert(InstType& inst, const Twine &name = "") const {
            return *irb.Insert(&inst, name);
        }
        
        constexpr BranchInst& branch(BasicBlock& dest) const {
            return *irb.CreateBr(&dest);
        }
        
        constexpr SwitchInst& switchCase(Value& value, BasicBlock& defaultDest, u32 numCasesEstimate = 10,
                MDNode* branchWeights = nullptr, MDNode* unpredictable = nullptr) const {
            return *irb.CreateSwitch(&value, &defaultDest, numCasesEstimate, branchWeights, unpredictable);
        }
    
        #undef alloca
        
        constexpr AllocaInst& alloca(Type& type, u32 addressSpace, Value& arraySize, const Twine& name = "") const {
            return *irb.CreateAlloca(&type, addressSpace, &arraySize, name);
        }
    
        constexpr AllocaInst& alloca(Type& type, u32 addressSpace, const Twine& name = "") const {
            return *irb.CreateAlloca(&type, addressSpace, nullptr, name);
        }
        
        constexpr AllocaInst& alloca(Type& type, Value& arraySize, const Twine& name = "") const {
            return *irb.CreateAlloca(&type, &arraySize, name);
        }
    
        constexpr AllocaInst& alloca(Type& type, const Twine& name = "") const {
            return *irb.CreateAlloca(&type, nullptr, name);
        }
        
        constexpr StoreInst& store(Value& value, Value& ptr, bool isVolatile = false) const {
            return *irb.CreateStore(&value, &ptr, isVolatile);
        }
        
    };
    
}

