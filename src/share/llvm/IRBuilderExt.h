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
        
        template <class InstType>
        constexpr InstType& insert(InstType& inst, const Twine &name = "") const {
            return *irb.Insert(&inst, name);
        }
        
        constexpr BranchInst& branch(BasicBlock& dest) const {
            return *irb.CreateBr(&dest);
        }
        
        constexpr SwitchInst& switchCase(Value& value, BasicBlock& defaultDest, u32 numCasesEstimate = 10,
                MDNode* branchWeights = nullptr, MDNode* unpredictable = nullptr) {
            return *irb.CreateSwitch(&value, &defaultDest, numCasesEstimate, branchWeights, unpredictable);
        }
        
    };
    
}

