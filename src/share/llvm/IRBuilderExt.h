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
        
        IRBuilder<> irb;
        
        template <class... Args>
        explicit IRBuilderExt(Args&& ... args) : irb(std::forward<Args...>(args)...) {}
        
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
                                 const Twine& name = "", MDNode* floatingPointMathTag = nullptr) {
            return *irb.CreateCall(callee, args, name, floatingPointMathTag);
        }
        
        constexpr CallInst& callIndex(FunctionCallee f, u64 index) {
            return call(f, {&constants().getInt(index)});
        }
        
        template <class InstType>
        constexpr InstType& insert(InstType& inst, const Twine& name = "") const {
            return *irb.Insert(&inst, name);
        }
        
        constexpr BranchInst& branch(BasicBlock& dest) {
            return *irb.CreateBr(&dest);
        }
        
        constexpr SwitchInst& switchCase(Value& value, BasicBlock& defaultDest, u32 numCasesEstimate = 10,
                                         MDNode* branchWeights = nullptr, MDNode* unpredictable = nullptr) {
            return *irb.CreateSwitch(&value, &defaultDest, numCasesEstimate, branchWeights, unpredictable);
        }
        
        #undef alloca
        
        constexpr AllocaInst& alloca(Type& type, u32 addressSpace, Value& arraySize, const Twine& name = "") {
            return *irb.CreateAlloca(&type, addressSpace, &arraySize, name);
        }
        
        constexpr AllocaInst& alloca(Type& type, u32 addressSpace, const Twine& name = "") {
            return *irb.CreateAlloca(&type, addressSpace, nullptr, name);
        }
        
        constexpr AllocaInst& alloca(Type& type, Value& arraySize, const Twine& name = "") {
            return *irb.CreateAlloca(&type, &arraySize, name);
        }
        
        constexpr AllocaInst& alloca(Type& type, const Twine& name = "") {
            return *irb.CreateAlloca(&type, nullptr, name);
        }
        
        constexpr LoadInst& load(Value& ptr, const char* name) {
            return *irb.CreateLoad(&ptr, name);
        }
        
        constexpr LoadInst& load(Value& ptr, const Twine& name = "") {
            return *irb.CreateLoad(&ptr, name);
        }
        
        constexpr LoadInst& load(Value& ptr, bool isVolatile, const Twine& name = "") {
            return *irb.CreateLoad(&ptr, isVolatile, name);
        }
        
        constexpr StoreInst& store(Value& value, Value& ptr, bool isVolatile = false) {
            return *irb.CreateStore(&value, &ptr, isVolatile);
        }
        
    };
    
}

