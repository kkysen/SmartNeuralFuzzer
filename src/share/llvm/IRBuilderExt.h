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
        
        explicit IRBuilderExt(const Module& module) : IRBuilderExt(module.getContext()) {}
    
        // do differentiate from templated version
        explicit IRBuilderExt(Module& module) : IRBuilderExt(static_cast<const Module&>(module)) {}
        
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
    
        constexpr IRBuilderExt& setInsertPoint(Instruction& inst) {
            irb.SetInsertPoint(&inst);
            return *this;
        }
        
        constexpr IRBuilderExt& setInsertPoint(BasicBlock& block, bool insertAtBeginning = false) {
            if (insertAtBeginning) {
                setInsertPoint(*block.getFirstInsertionPt());
            } else {
                irb.SetInsertPoint(&block);
            }
            return *this;
        }
        
        constexpr IRBuilderExt& setInsertPoint(BasicBlock& block, BasicBlock::iterator iterator) {
            irb.SetInsertPoint(&block, iterator);
            return *this;
        }
    
        constexpr IRBuilderExt& setInsertPoint(Function& function, bool insertAtBeginning = false) {
            return setInsertPoint(insertAtBeginning ? function.front() : function.back(), insertAtBeginning);
        }
        
        constexpr BasicBlock::iterator insertPoint() const {
            return irb.GetInsertPoint();
        }
        
        constexpr BasicBlock& block() const {
            return *irb.GetInsertBlock();
        }
        
        constexpr Function& function() const {
            return *block().getParent();
        }
        
        constexpr Module& module() const {
            return *function().getParent();
        }
    
        constexpr CallInst& call(FunctionCallee callee, ArrayRef<Value*> args, ArrayRef<OperandBundleDef> operandBundles,
                const Twine& name = "", MDNode* floatingPointMathTag = nullptr) {
            return *irb.CreateCall(callee, args, operandBundles, name, floatingPointMathTag);
        }
        
        constexpr CallInst& call(FunctionCallee callee, ArrayRef<Value*> args = None,
                                 const Twine& name = "", MDNode* floatingPointMathTag = nullptr) {
            return *irb.CreateCall(callee, args, name, floatingPointMathTag);
        }
        
        constexpr CallInst& callIndex(FunctionCallee f, u64 index) {
            return call(f, {&constants().getInt(index)});
        }
        
        constexpr InvokeInst& invoke(FunctionCallee callee, BasicBlock& normalDest, BasicBlock& unwindDest,
                ArrayRef<Value*> args, ArrayRef<OperandBundleDef> operandBundles, const Twine& name = "") {
            return *irb.CreateInvoke(callee, &normalDest, &unwindDest, args, operandBundles, name);
        }
    
        constexpr InvokeInst& invoke(FunctionCallee callee, BasicBlock& normalDest, BasicBlock& unwindDest,
                ArrayRef<Value*> args = None, const Twine& name = "") {
            return *irb.CreateInvoke(callee, &normalDest, &unwindDest, args, name);
        }
    
        constexpr CallBrInst& callBr(FunctionCallee callee, BasicBlock& defaultDest, ArrayRef<BasicBlock*> indirectDests,
                ArrayRef<Value*> args, ArrayRef<OperandBundleDef> operandBundles, const Twine& name = "") {
            return *irb.CreateCallBr(callee, &defaultDest, indirectDests, args, operandBundles, name);
        }
        
        constexpr CallBrInst& callBr(FunctionCallee callee, BasicBlock& defaultDest, ArrayRef<BasicBlock*> indirectDests,
                ArrayRef<Value*> args = None, const Twine& name = "") {
            return *irb.CreateCallBr(callee, &defaultDest, indirectDests, args, name);
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

