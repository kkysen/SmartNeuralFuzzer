//
// Created by Khyber on 2/14/2019.
//

#include "src/main/pass/coverage/includes.h"

#include "llvm/IR/CFG.h"

namespace llvm::pass::coverage::branch {
    
    class BranchCoveragePass : public ModulePass {
    
    private:
        
        struct OnBranch {
            const FunctionCallee single;
            const FunctionCallee multi;
            const FunctionCallee switchCase;
            const FunctionCallee infinite;
        };
        
        class BlockPass {
        
        private:
            
            const OnBranch& onBranch;
            BasicBlock& block;
        
        public:
            
            constexpr BlockPass(const OnBranch& onBranch, BasicBlock& block) noexcept
                    : onBranch(onBranch), block(block) {}

        private:
    
            #define _(block, InstType, func) \
                if (isa<InstType>(block)) { \
                    traced |= func(cast<InstType>(block)); \
                } \

            bool traceTerminator() {
                auto* const terminatorPtr = block.getTerminator();
                if (!terminatorPtr) {
                    return false;
                }
                auto& terminator = *terminatorPtr;

                bool traced = false;
                _(terminator, BranchInst, traceBranch)
                else _(terminator, CallBase, traceIndirectCall)
                else _(terminator, SwitchInst, traceSwitch)
                else _(terminator, IndirectBrInst, traceIndirectBranch)
                return traced;
            }
            
            bool traceNonTerminators() {
                // CallBase = CallInst, InvokeInst, CallBrInst
                // InvokeInst and CallBrInst are terminators
                bool traced = false;
                for (auto& inst : block) {
                    _(inst, CallInst, traceIndirectCall)
                }
                return traced;
            }
    
            #undef _
            
        public:
            
            bool trace() {
                const bool tracedTerminator = traceTerminator();
                const bool tracedNonTerminators = traceNonTerminators();
                return tracedTerminator || tracedNonTerminators;
            }
        
        private:
            
            bool traceCondition(Instruction& inst, Value* conditionPtr) const {
                if (!conditionPtr) {
                    return false;
                }
                auto& condition = *conditionPtr;
                IRBuilder<> builder(&inst);
                IRBuilderExt ext(builder);
                ext.call(onBranch.single, {&condition});
                return true;
            }
            
            bool traceBranch(BranchInst& inst) const {
                if (!inst.isConditional()) {
                    return false;
                }
                return traceCondition(inst, inst.getCondition());
            }
            
            bool traceSelectCall(Instruction& inst, SelectInst& selectInst) const {
                if (!selectInst.getCondition()) {
                    return false;
                }
                return traceCondition(inst, selectInst.getCondition());
            }
            
            bool traceTrueIndirectCall(Instruction& inst) const {
                IRBuilder<> builder(&inst);
                IRBuilderExt ext(builder);
                ext.call(onBranch.infinite);
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
                
                if (!isa<SelectInst>(functionPtr)) {
                    return traceSelectCall(inst, cast<SelectInst>(functionPtr));
                } else {
                    return traceTrueIndirectCall(inst);
                }
            }
            
            void traceMultiBranch(BasicBlock& block, u64 branchNum, u64 numBranches) const {
                IRBuilder<> builder(&block.front());
                IRBuilderExt ext(builder);
                const auto constants = ext.constants();
                ext.call(onBranch.multi, {&constants.getInt(branchNum), &constants.getInt(numBranches)});
            }
            
            void traceSwitchCase(BasicBlock& block, Value& validPtr, u64 caseNum, u64 numCases) const {
                IRBuilder<> builder(&block.front());
                IRBuilderExt ext(builder);
                const auto constants = ext.constants();
                Value* valid = builder.CreateLoad(&validPtr);
                ext.call(onBranch.switchCase, {valid, &constants.getInt(caseNum), &constants.getInt(numCases)});
                builder.CreateStore(&constants.getInt(false), &validPtr);
            }
            
            class SwitchCaseSuccessors {
            
            private:
                
                using BlockSet = SmallPtrSet<BasicBlock*, 8>;
                
                BlockSet successors;
            
            public:
                
                constexpr u32 numBranches() const noexcept {
                    return successors.size();
                }
                
                constexpr const BlockSet& get() const noexcept {
                    return successors;
                }
                
                // each branch can have multiple cases
                // i.e., multiple cases can go to the same successor block,
                // but it's only 1 real branch in that case
                void findUniqueBranches(SwitchInst& switchInst) {
                    BasicBlock* successor = switchInst.case_default()->getCaseSuccessor();
                    if (successor) {
                        successors.insert(successor);
                    }
                    const BasicBlock* lastSuccessor = successor;
                    for (const auto& caseHandle : switchInst.cases()) {
                        BasicBlock* successor = caseHandle.getCaseSuccessor();
                        // cases are usually already in order, so this is just an optimization
                        if (!successor || successor == lastSuccessor) {
                            continue;
                        }
                        successors.insert(successor);
                        lastSuccessor = successor;
                    }
                }
                
                // find if there are any successors with non-unique predecessors (i.e. fallthrough cases)
                // for these pairs, we need to use the onSwitchCase() API instead of just onMultiBranch()
                bool hasFallThroughCases(BasicBlock& switchBlock) const {
                    for (BasicBlock* successor : successors) {
                        for (BasicBlock* predecessor : llvm::predecessors(successor)) {
                            if (predecessor != &switchBlock) {
                                return true;
                            }
                        }
                    }
                    return false;
                }
                
                Value& createValidPtr(SwitchInst& switchInst) const {
                    // sometimes the default case block is jumped to from outside of the switch instruction
                    // so we get an error "Instruction does not dominate all uses"
                    // since the validPtr won't have been defined in that jump
                    // if we insert the validPtr right before the switch instruction
                    // instead, it's easier to just put it at the end of the first block of the function
                    IRBuilder<> builder(switchInst.getParent()->getParent()->front().getTerminator());
                    IRBuilderExt ext(builder);
                    Value& validPtr = *builder.CreateAlloca(ext.types().get<bool>());
                    builder.CreateStore(&ext.constants().getInt(true), &validPtr);
                    return validPtr;
                }
                
            };
            
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
                u32 i = 0;
                if (!hasFallThroughCases) {
                    // for these successors, we can still use the raw onMultiBranch() API
                    for (BasicBlock* successor : successors.get()) {
                        traceMultiBranch(*successor, i++, numBranches);
                    }
                } else {
                    // for these successors, we have to use the onSwitchCase() API
                    // with the bool flag used to ensure only one onMultiBranch() is called
                    Value& validPtr = successors.createValidPtr(inst);
                    for (BasicBlock* successor : successors.get()) {
                        traceSwitchCase(*successor, validPtr, i++, numBranches);
                    }
                }
                
                return true;
            }
            
            bool traceIndirectBranch(IndirectBrInst&) const {
                llvm_unreachable("indirectbr not supported yet");
            }
            
        };
    
    public:
        
        static char ID;
        
        BranchCoveragePass() : ModulePass(ID) {}
        
        StringRef getPassName() const override {
            return "Branch Coverage Pass";
        }
        
        bool runOnModule(Module& module) override {
            const Api api("BranchCoverage", module);
            const OnBranch onBranch = {
                    .single = api.func<void, bool>("onSingleBranch"),
                    .multi = api.func<void, u64, u64>("onMultiBranch"),
                    .switchCase = api.func<void, bool, u64, u64>("onSwitchCase"),
                    .infinite = api.func<void>("onInfiniteBranch"),
            };
            const auto onFunction = api.func<void, u64>("onFunction");
            u64 functionIndex = 0;
            const bool modified = filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        return BlockPass(onBranch, block).trace();
                    }, [&](Function& function) {
                        IRBuilder<> builder(&*function.getEntryBlock().getFirstInsertionPt());
                        IRBuilderExt ext(builder);
                        ext.call(onFunction, {&ext.constants().getInt(functionIndex++)});
                    });
            api.global<u64>("numFunctions", Api::GlobalArgs {
                .isConstant = true,
                .initializer = Constants(module.getContext()).getInt(functionIndex),
            });
            return modified;
        }
        
    };
    
    char BranchCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BranchCoveragePass>();
    
}
