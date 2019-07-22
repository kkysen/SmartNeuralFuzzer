//
// Created by Khyber on 7/18/2019.
//

#include "src/share/llvm/CallBaseHack.h"

#include "src/share/llvm/operandBundles.h"

namespace {
    
    using namespace llvm;
    
    auto calcNumOperands(const CallBase& inst, ArrayRef<Value*> args) noexcept {
        return inst.getNumOperands() - (inst.arg_size() - args.size());
    }
    
}

namespace llvm {
    
    CallBaseHack::SubClassData CallBaseHack::getSubClassData(const CallBase& inst) {
        // CallBrInst is the only subclass with more data
        switch (inst.getOpcode()) {
            case Instruction::CallBr:
                return reinterpret_cast<const CallBaseHack&>(inst).subClassData;
            default:
                return {};
        }
    }
    
    CallBaseHack::CallBaseHack(const CallBase& inst, ArrayRef<Value*> args)
            : CallBase(
            inst.getAttributes(),
            inst.getFunctionType(),
            inst.getType(),
            inst.getOpcode(),
            OperandTraits<CallBase>::op_end(this) - calcNumOperands(inst, args),
            calcNumOperands(inst, args)),
              subClassData(getSubClassData(inst)) {
        setCallingConv(inst.getCallingConv());
        std::copy(args.begin(), args.end(), op_begin());
        std::copy(inst.bundle_op_info_begin(), inst.bundle_op_info_end(), bundle_op_info_begin());
        setInstructionSubclassData(reinterpret_cast<const CallBaseHack&>(inst).getSubclassDataFromInstruction());
        SubclassOptionalData = inst.getRawSubclassOptionalData();
    }
    
    CallBase& CallBaseHack::cloneWithNewArgsImpl(const CallBase& inst, ArrayRef<Value*> args) {
        const FunctionCallee func = {inst.getFunctionType(), inst.getCalledOperand()};
        const auto operandBundles = getOperandBundles(inst);
        const auto name = inst.getName();
        if (!operandBundles.empty()) {
            llvm_unreachable("operandBundles not supported yet");
        }
        switch (inst.getOpcode()) {
            case Instruction::Call: {
                return *CallInst::Create(func, args, operandBundles, name);
            }
            case Instruction::Invoke: {
                const auto& invoke = cast<InvokeInst>(inst);
                return *InvokeInst::Create(func, invoke.getNormalDest(), invoke.getUnwindDest(), args, name);
            }
            case Instruction::CallBr: {
                const auto& callBr = cast<CallBrInst>(inst);
                return *CallBrInst::Create(func, callBr.getDefaultDest(), callBr.getIndirectDests(), args, name);
            }
            default:
                llvm_unreachable("invalid CallBase opcode");
        }
        
        CallBaseHack hack(inst, args);
        return reinterpret_cast<CallBase&>(*hack.clone());
    }
    
}
