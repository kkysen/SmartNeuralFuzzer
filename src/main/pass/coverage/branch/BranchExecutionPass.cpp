//
// Created by Khyber on 6/24/2019.
//

#include "src/main/pass/coverage/includes.h"

#include "src/main/runtime/coverage/BranchExecutionRuntime.h"
#include "src/main/pass/coverage/branch/SwitchCaseSuccessors.h"

namespace llvm::pass::coverage::branch {
    
    class BranchExecutionPass : public ModulePass {
    
    private:
        
        struct NextBranch {
            const FunctionCallee single;
            const FunctionCallee multi;
            const FunctionCallee infinite;
        };
        
        struct Api {
            const NextBranch nextBranch;
            const FunctionCallee onEdge;
            FunctionType& funcType;
        };
        
        class InstructionPass {
        
        private:
            
            const Api& api;
            Instruction& instruction;
            IRBuilderExt& irbe;
        
        public:
            
            constexpr InstructionPass(const Api& api, Instruction& instruction, IRBuilderExt& irbe) noexcept
                    : api(api), instruction(instruction), irbe(irbe) {}
        
        private:
            
            void transformBranch(BranchInst& inst) const {
                if (inst.isConditional()) {
                    irbe.setInsertPoint(inst);
                    auto& condition = irbe.call(api.nextBranch.single, {});
                    inst.setCondition(&condition);
                }
            }
            
            void transformSwitch(SwitchInst& inst) const {
                SwitchCaseSuccessors successors;
                successors.findUniqueBranches(inst);
                const auto numBranches = successors.numBranches();
                // TODO preserve branch weights if possible
                irbe.setInsertPoint(inst);
                inst.removeFromParent();
                auto& switchValue = irbe.call(api.nextBranch.multi, {&irbe.constants().getInt(numBranches)});
                auto& switchInst = irbe.switchCase(switchValue, *inst.getDefaultDest(), numBranches);
                u64 i = 0;
                for (auto* successor : successors.get()) {
                    switchInst.addCase(&irbe.constants().getInt(i++), successor);
                }
            }
            
            void transformSelectCall(CallBase& inst, SelectInst& select) const {
                if (!select.getCondition()) {
                    return;
                }
                select.removeFromParent();
                inst.removeFromParent();
                auto& condition = irbe.call(api.nextBranch.single, {});
                select.setCondition(&condition);
                irbe.insert(select);
            }
            
            void transformTrueIndirectCall(CallBase& inst) const {
                inst.removeFromParent();
                auto& functionPtr = irbe.call(api.nextBranch.infinite, {});
                inst.setCalledOperand(&functionPtr);
            }
            
            void transformIndirectCall(CallBase& inst) const {
                auto& functionPtr = *inst.getCalledOperand();
                if (isa<SelectInst>(functionPtr)) {
                    transformSelectCall(inst, cast<SelectInst>(functionPtr));
                } else {
                    transformTrueIndirectCall(inst);
                }
            }
            
            void transformCall(CallBase& inst) const {
                if (!inst.getCalledOperand()) {
                    return;
                }
                if (inst.isIndirectCall()) {
                    transformIndirectCall(inst);
                } else {
                    auto& func = *inst.getCalledFunction();
                    if (func.isDeclaration() || runtimeFunctionFilter()(func.getName())) {
                        return;
                    }
                }
                irbe.insert(inst);
                inst.mutateFunctionType(&api.funcType);
            }
            
            void transformIndirectBranch(IndirectBrInst&) const {
                llvm_unreachable("indirectbr not supported yet");
                // TODO
            }
            
            void transformTerminator() const {
                switch (instruction.getOpcode()) {
                    case Instruction::Br:
                        return transformBranch(cast<BranchInst>(instruction));
                    case Instruction::Switch:
                        return transformSwitch(cast<SwitchInst>(instruction));
                    case Instruction::Invoke:
                    case Instruction::CallBr:
                        return transformCall(cast<CallBase>(instruction));
                    case Instruction::IndirectBr:
                        return transformIndirectBranch(cast<IndirectBrInst>(instruction));
                    default: {
                        instruction.removeFromParent();
                        irbe.insert(instruction);
                        return;
                    }
                }
            }
            
            void transformNonTerminator() const {
                switch (instruction.getOpcode()) {
                    case Instruction::Call:
                        return transformCall(cast<CallBase>(instruction));
                }
            }
        
        public:
            
            void transform() const {
                if (instruction.isTerminator()) {
                    transformTerminator();
                } else {
                    transformNonTerminator();
                }
            }
            
            void operator()() const {
                transform();
            }
            
        };
        
        class BlockPass {
        
        private:
            
            const Api& api;
            BasicBlock& block;
            IRBuilderExt& irbe;
        
        public:
            
            BlockPass(const Api& api, BasicBlock& block, IRBuilderExt& irbe) noexcept
                    : api(api), block(block), irbe(irbe) {}
            
            bool transform() {
                for (auto& inst : block) {
                    InstructionPass(api, inst, irbe)();
                }
                return true;
            }
            
            bool operator()() {
                return transform();
            }
            
        };
    
    public:
        
        static char ID;
        
        BranchExecutionPass() : ModulePass(ID) {}
        
        StringRef getPassName() const override {
            return "Branch Execution Pass";
        }
        
        bool runOnModule(Module& module) override {
            using llvm::Api;
            const Api api("BranchExecution", module);
            using runtime::coverage::branch::execute::Func;
            const BranchExecutionPass::Api ownApi = {
                    .nextBranch = {
                            .single = api.func<bool()>("nextSingleBranch"),
                            .multi = api.func<u64(u64)>("nextMultiBranch"),
                            .infinite = api.func<Func*()>("nextInfiniteBranch"),
                    },
                    .onEdge = api.func<void(u64, u64)>("onEdge"),
                    .funcType = api.types.func<Func>(),
            };
            SmallVector<Constant*, 0> functions;
            IRBuilderExt irbe(module);
            const bool modified = filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        return BlockPass(ownApi, block, irbe)();
                    }, [&](Function& function) {
                        functions.emplace_back(&function);
                        // make all functions 0 arg and void, i.e. void()
                        function.mutateType(&ownApi.funcType);
                    });
            api.global<u64>("numFunctions", Api::GlobalArgs {
                    .module = &module,
                    .isConstant = true,
                    .initializer = Constants(module.getContext()).getInt(functions.size()),
            });
            api.global(
                    "functions",
                    api.types.array<Func>(functions.size()),
                    Api::GlobalArgs {
                            .module = &module,
                            .isConstant = true,
                            .initializer = *ConstantDataArray::get(module.getContext(), functions),
                    });
            return modified;
        }
        
    };
    
    char BranchExecutionPass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BranchExecutionPass>();
    
}
