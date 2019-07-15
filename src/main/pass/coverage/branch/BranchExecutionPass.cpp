//
// Created by Khyber on 6/24/2019.
//

#include "src/main/pass/coverage/includes.h"

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
        };
        
        class InstructionPass {
        
        private:
            
            const Api& api;
            Instruction& instruction;
            IRBuilder<>& irb;
            IRBuilderExt irbe;
        
        public:
            
            constexpr InstructionPass(const Api& api, Instruction& instruction, IRBuilder<>& irb) noexcept
                    : api(api), instruction(instruction), irb(irb), irbe(irb) {}
            
        private:
    
            void transformBranch(BranchInst& inst) {
                inst.removeFromParent();
                if (inst.isConditional()) {
                    auto& condition = irbe.call(api.nextBranch.single, {});
                    inst.setCondition(&condition);
                }
                irbe.insert(inst);
            }
    
            void transformSwitch(SwitchInst& inst) {
                const auto numCases = inst.getNumCases();
                auto& defaultDest = *inst.getDefaultDest();
                if (numCases <= 1) {
                    // unconditionally jump to default case
                    irbe.branch(defaultDest);
                    return;
                }
    
                SwitchCaseSuccessors successors;
                successors.findUniqueBranches(inst);
                const auto numBranches = successors.numBranches();
                if (numBranches <= 1) {
                    // still an unconditional jump to the same successor block
                    irbe.branch(**successors.get().begin());
                    return;
                }
                // TODO preserve branch weights if possible
                auto& switchValue = irbe.call(api.nextBranch.multi, {&irbe.constants().getInt(numBranches)});
                auto& switchInst = irbe.switchCase(switchValue, defaultDest, numBranches);
                u64 i = 0;
                for (auto* successor : successors.get()) {
                    switchInst.addCase(&irbe.constants().getInt(i++), successor);
                }
            }
            
            void transformSelectCall(CallBase& inst, SelectInst& select) {
                if (!select.getCondition()) {
                    return;
                }
                select.removeFromParent();
                inst.removeFromParent();
                auto& condition = irbe.call(api.nextBranch.single, {});
                select.setCondition(&condition);
                irbe.insert(select);
                irbe.insert(inst);
            }
            
            void transformTrueIndirectCall(CallBase& inst) {
                inst.removeFromParent();
                auto& functionPtr = irbe.call(api.nextBranch.infinite, {});
                inst.setCalledOperand(&functionPtr);
                irbe.insert(inst);
            }
    
            void transformIndirectCall(CallBase& inst) {
                if (!inst.isIndirectCall()) {
                    return;
                }
                if (!inst.getCalledOperand()) {
                    return;
                }
                auto& functionPtr = *inst.getCalledOperand();
                if (isa<SelectInst>(functionPtr)) {
                    transformSelectCall(inst, cast<SelectInst>(functionPtr));
                } else {
                    transformTrueIndirectCall(inst);
                }
            }
            
            void transformIndirectBranch(IndirectBrInst&) const {
                llvm_unreachable("indirectbr not supported yet");
                // TODO
            }

        public:
            
            void transformTerminator() {
                switch (instruction.getOpcode()) {
                    case Instruction::Br:
                        return transformBranch(cast<BranchInst>(instruction));
                    case Instruction::Switch:
                        return transformSwitch(cast<SwitchInst>(instruction));
                    case Instruction::Invoke:
                    case Instruction::CallBr:
                        return transformIndirectCall(cast<CallBase>(instruction));
                    case Instruction::IndirectBr:
                        return transformIndirectBranch(cast<IndirectBrInst>(instruction));
                    default: {
                        instruction.removeFromParent();
                        irbe.insert(instruction);
                        return;
                    }
                }
            }
            
            void transformNonTerminator() {
                switch (instruction.getOpcode()) {
                    case Instruction::Call:
                        return transformIndirectCall(cast<CallBase>(instruction));
                }
            }
    
            void transform() {
                if (instruction.isTerminator()) {
                    transformTerminator();
                } else {
                    transformNonTerminator();
                }
            }
    
            void operator()() {
                transform();
            }
            
        };
        
        class BlockPass {
        
        private:
            
            using Instructions = typename BasicBlock::InstListType;
            
            const Api& api;
            struct {
                BasicBlock& modified;
                Instructions original;
            } block;
            IRBuilder<> irb;
            
            void init() noexcept {
                block.original.swap(block.modified.getInstList());
            }
        
        public:
            
            BlockPass(const Api& api, BasicBlock& block) noexcept
                    : api(api), block({block, {}}), irb(&block) {
                init();
            }
            
            bool transform() {
                for (auto& inst : block.original) {
                    InstructionPass(api, inst, irb)();
                }
                // need to delete all instructions in block.original
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
            return "Branch Coverage Pass";
        }
        
        bool runOnModule(Module& module) override {
            using llvm::Api;
            const Api api("BranchExecution", module);
            const BranchExecutionPass::Api ownApi = {
                    .nextBranch = {
                            .single = api.func<bool>("nextSingleBranch"),
                            .multi = api.func<u64, u64>("nextMultiBranch"),
                            .infinite = api.func<const void*>("nextInfiniteBranch"),
                    },
                    .onEdge = api.func<void, u64, u64>("onEdge"),
            };
            SmallVector<Constant*, 0> functions;
            const bool modified = filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        return BlockPass(ownApi, block)();
                    }, [&](Function& function) {
                        functions.emplace_back(&function);
                    });
            api.global<u64>("numFunctions", Api::GlobalArgs {
                    .isConstant = true,
                    .initializer = Constants(module.getContext()).getInt(functions.size()),
            });
            api.global(
                    "functions",
                    *ArrayType::get(api.types.get<const void*>(), functions.size()),
                    Api::GlobalArgs {
                            .isConstant = true,
                            .initializer = *ConstantDataArray::get(module.getContext(), functions),
                    });
            return modified;
        }
        
    };
    
    char BranchExecutionPass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BranchExecutionPass>();
    
}
