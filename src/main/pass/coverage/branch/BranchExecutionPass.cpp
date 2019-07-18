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
                inst.removeFromParent();
                if (inst.isConditional()) {
                    auto& condition = irbe.call(api.nextBranch.single, {});
                    inst.setCondition(&condition);
                }
                irbe.insert(inst);
            }
            
            void transformSwitch(SwitchInst& inst) const {
                SwitchCaseSuccessors successors;
                successors.findUniqueBranches(inst);
                const auto numBranches = successors.numBranches();
                // TODO preserve branch weights if possible
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
                    inst.removeFromParent();
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
                if (__builtin_expect(instruction.isTerminator(), false)) {
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
            
            class BlockTransform {
            
            public:
                
                using Instructions = typename BasicBlock::InstListType;
    
                BasicBlock& modified;
                Instructions original;
                
                explicit BlockTransform(BasicBlock& realOriginal)
                        : modified(realOriginal), original({}) {
                    original.splice(original.begin(), modified.getInstList());
                }
                
            };
            
            const Api& api;
            BlockTransform block;
            IRBuilderExt& irbe;
        
        public:
            
            BlockPass(const Api& api, BasicBlock& originalBlock, IRBuilderExt& irbe) noexcept
                    : api(api), block(originalBlock), irbe(irbe) {
                irbe.setInsertPoint(block.modified);
            }
            
            bool transform() {
                for (auto it = block.original.begin(); it != block.original.end();) {
                    // it++ is necessary b/c inst might be removed,
                    // so we need to advance the iterator first before using the current value
                    auto& inst = *(it++);
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
            u64 blockIndex = 0;
            const bool modified = filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        errs() << '\t' << "BranchExecution: block: " << blockIndex++;
//                        errs() << block;
                        const bool ret = BlockPass(ownApi, block, irbe)();
//                        errs() << block;
                        return ret;
                    }, [&](Function& function) {
                        errs() << "BranchExecution: function: " << function.getName() << '\n';
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
