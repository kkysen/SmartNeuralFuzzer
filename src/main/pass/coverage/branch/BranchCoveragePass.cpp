//
// Created by Khyber on 2/14/2019.
//

#include "src/main/pass/coverage/includes.h"

#include "src/main/pass/coverage/branch/SwitchCaseSuccessors.h"

namespace llvm::pass::coverage::branch {
    
    class BranchCoveragePass : public ModulePass {
    
    private:
        
        struct OnBranch {
            const FunctionCallee single;
            const FunctionCallee multi;
            const FunctionCallee switchCase;
            const FunctionCallee infinite;
        };
        
        struct Api {
            OnBranch onBranch;
        };
        
        class BlockPass {
        
        private:
            
            const Api& api;
            BasicBlock& block;
            IRBuilderExt& irbe;
        
        public:
            
            constexpr BlockPass(const Api& api, BasicBlock& block, IRBuilderExt& irbe) noexcept
                    : api(api), block(block), irbe(irbe) {}
        
        private:
            
            bool traceCondition(Instruction& inst, Value* conditionPtr) const {
                if (!conditionPtr) {
                    return false;
                }
                auto& condition = *conditionPtr;
                irbe.setInsertPoint(inst);
                irbe.call(api.onBranch.single, {&condition});
                return true;
            }
            
            bool traceBranch(BranchInst& inst) const {
                if (!inst.isConditional()) {
                    return false;
                }
                return traceCondition(inst, inst.getCondition());
            }
            
            bool traceSelectCall(Instruction& inst, SelectInst& select) const {
                if (!select.getCondition()) {
                    return false;
                }
                return traceCondition(inst, select.getCondition());
            }
            
            bool traceTrueIndirectCall(CallBase& inst) const {
                irbe.setInsertPoint(inst);
                irbe.call(api.onBranch.infinite);
                return true;
            }
            
            bool traceIndirectCall(CallBase& inst) const {
                if (!inst.isIndirectCall()) {
                    return false;
                }
                if (!inst.getCalledOperand()) {
                    return false;
                }
                auto& functionPtr = *inst.getCalledOperand();
                
                if (isa<SelectInst>(functionPtr)) {
                    return traceSelectCall(inst, cast<SelectInst>(functionPtr));
                } else {
                    return traceTrueIndirectCall(inst);
                }
            }
            
            void traceMultiBranch(BasicBlock& block, u64 branchNum, u64 numBranches) const {
                irbe.setInsertPoint(block, true);
                const auto constants = irbe.constants();
                irbe.call(api.onBranch.multi, {&constants.getInt(branchNum), &constants.getInt(numBranches)});
            }
            
            void traceSwitchCase(BasicBlock& block, Value& validPtr, u64 caseNum, u64 numCases) const {
                irbe.setInsertPoint(block, true);
                const auto constants = irbe.constants();
                auto& valid = irbe.load(validPtr);
                irbe.call(api.onBranch.switchCase, {&valid, &constants.getInt(caseNum), &constants.getInt(numCases)});
                irbe.store(constants.getInt(false), validPtr);
            }
            
            bool traceSwitch(SwitchInst& inst) const {
                const auto numCases = inst.getNumCases() + 1;
                if (numCases <= 1) {
                    // unconditionally jump to default case
                    return false;
                }
                
                SwitchCaseSuccessors successors;
                successors.findUniqueBranches(inst);
                const auto numBranches = successors.numBranches();
                if (numBranches <= 1) {
                    // still an unconditional jump to the same successor block
                    return false;
                }
                
                const bool hasFallThroughCases = successors.hasFallThroughCases(block);
                u64 i = 0;
                if (!hasFallThroughCases) {
                    // for these successors, we can still use the raw onMultiBranch() API
                    for (BasicBlock* successor : successors.get()) {
                        traceMultiBranch(*successor, i++, numBranches);
                    }
                } else {
                    // for these successors, we have to use the onSwitchCase() API
                    // with the bool flag used to ensure only one onMultiBranch() is called
                    Value& validPtr = successors.createValidPtr(inst, irbe);
                    for (BasicBlock* successor : successors.get()) {
                        traceSwitchCase(*successor, validPtr, i++, numBranches);
                    }
                }
                
                return true;
            }
            
            bool traceIndirectBranch(IndirectBrInst&) const {
                llvm_unreachable("indirectbr not supported yet");
                // TODO
            }
            
            bool traceTerminator(Instruction& inst) {
                switch (inst.getOpcode()) {
                    case Instruction::Br:
                        return traceBranch(cast<BranchInst>(inst));
                    case Instruction::Switch:
                        return traceSwitch(cast<SwitchInst>(inst));
                    case Instruction::Invoke:
                    case Instruction::CallBr:
                        return traceIndirectCall(cast<CallBase>(inst));
                    case Instruction::IndirectBr:
                        return traceIndirectBranch(cast<IndirectBrInst>(inst));
                }
                return false;
            }
            
            bool traceNonTerminator(Instruction& inst) {
                switch (inst.getOpcode()) {
                    case Instruction::Call:
                        return traceIndirectCall(cast<CallBase>(inst));
                }
                return false;
            }
        
        public:
            
            bool trace() {
                bool traced = false;
                for (auto& inst : block) {
                    if (inst.isTerminator()) {
                        traced |= traceTerminator(inst);
                    } else {
                        traced |= traceNonTerminator(inst);
                    }
                }
                return traced;
            }
            
            bool operator()() {
                return trace();
            }
            
        };
    
    public:
        
        static char ID;
        
        BranchCoveragePass() : ModulePass(ID) {}
        
        StringRef getPassName() const override {
            return "Branch Coverage Pass";
        }
        
        bool runOnModule(Module& module) override {
            using llvm::Api;
            const Api api("BranchCoverage", module);
            const BranchCoveragePass::Api ownApi = {
                    .onBranch = {
                            .single = api.func<void(bool)>("onSingleBranch"),
                            .multi = api.func<void(u64, u64)>("onMultiBranch"),
                            .switchCase = api.func<void(bool, u64, u64)>("onSwitchCase"),
                            .infinite = api.func<void()>("onInfiniteBranch"),
                    },
            };
            const auto onFunction = api.func<void(u64)>("onFunction");
            IRBuilderExt irbe(module);
            u64 functionIndex = 0;
            const bool modified = filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        return BlockPass(ownApi, block, irbe)();
                    }, [&](Function& function) {
                        irbe.setInsertPoint(*function.getEntryBlock().getFirstInsertionPt());
                        irbe.call(onFunction, {&irbe.constants().getInt(functionIndex++)});
                    });
            api.global<u64>("numFunctions", Api::GlobalArgs {
                    .module = &module,
                    .isConstant = true,
                    .initializer = Constants(module.getContext()).getInt(functionIndex),
            });
            return modified;
        }
        
    };
    
    char BranchCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BranchCoveragePass>();
    
}
