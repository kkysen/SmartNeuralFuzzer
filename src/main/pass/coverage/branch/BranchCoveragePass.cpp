//
// Created by Khyber on 2/14/2019.
//

#include "src/main/pass/coverage/includes.h"

#include "llvm/IR/CFG.h"

namespace llvm::pass::coverage::branch {
    
    class BranchCoveragePass : public ModulePass {
    
    private:
        
        struct Flags {
            bool branches;
            bool switches;
            bool indirectCalls;
        } flags {
                .branches = true,
                .switches = true,
                .indirectCalls = false,
        };
        
        struct OnBranch {
            const FunctionCallee single;
            const FunctionCallee multi;
            const FunctionCallee switchCase;
            const FunctionCallee infinite;
        };
        
        class BlockPass {
        
        private:
            
            const Flags& flags;
            const OnBranch& onBranch;
            BasicBlock& block;
        
        public:
            
            constexpr BlockPass(const Flags& flags, const OnBranch& onBranch, BasicBlock& block) noexcept
                    : flags(flags), onBranch(onBranch), block(block) {}
            
            bool trace() {
                auto* const terminatorPtr = block.getTerminator();
                if (!terminatorPtr) {
                    return false;
                }
                auto& terminator = *terminatorPtr;
                
                #define _(block, InstType, func) \
                if (isa<InstType>(block)) { \
                    traced |= func(cast<InstType>(block)); \
                } \

                bool traced = false;
                
                _(terminator, BranchInst, traceBranch)
                else _(terminator, CallBase, traceIndirectCall)
                else _(terminator, SwitchInst, traceSwitch)
                
                // CallBase = CallInst, InvokeInst, CallBrInst
                // InvokeInst and CallBrInst are terminators
                for (auto& inst : block) {
                    _(inst, CallInst, traceIndirectCall)
                }
                
                return traced;
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
                if (!flags.branches) {
                    return false;
                }
                if (!inst.isConditional()) {
                    return false;
                }
                return traceCondition(inst, inst.getCondition());
            }
            
            bool traceSelectCall(Instruction& inst, SelectInst& selectInst) const {
                if (!flags.branches) {
                    return false;
                }
                if (!selectInst.getCondition()) {
                    return false;
                }
                return traceCondition(inst, selectInst.getCondition());
            }
            
            bool traceTrueIndirectCall(Instruction& inst, Value& functionPointer) const {
                if (!flags.indirectCalls) {
                    return false;
                }
                IRBuilder<> builder(&inst);
                IRBuilderExt ext(builder);
                ext.call(onBranch.infinite, {&functionPointer});
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
                    return traceTrueIndirectCall(inst, functionPtr);
                }
            }
            
            void traceMultiBranch(BasicBlock& block, u32 branchNum) const {
                IRBuilder<> builder(&block.front());
                IRBuilderExt ext(builder);
                const auto constants = ext.constants();
                ext.call(onBranch.multi, {constants.getInt(branchNum)});
            }
            
            void traceSwitchCase(BasicBlock& block, Value& validPtr, u32 caseNum) const {
                IRBuilder<> builder(&block.front());
                IRBuilderExt ext(builder);
                const auto constants = ext.constants();
                Value* valid = builder.CreateLoad(&validPtr);
                ext.call(onBranch.switchCase, {valid, constants.getInt(caseNum)});
                builder.CreateStore(constants.getInt(false), &validPtr);
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
                    builder.CreateStore(ext.constants().getInt(true), &validPtr);
                    return validPtr;
                }
                
            };
            
            /**
             * Trace a switch instruction
             * by calling onMultiBranch(caseNum, numCases)
             * as the first statement of each case's BasicBlock.
             */
            bool traceSwitch(SwitchInst& inst) const {
                if (!flags.switches) {
                    return false;
                }
                
                const auto numCases = inst.getNumCases() + 1;
                if (numCases <= 1) {
                    // unconditionally jump to default case
                    return false;
                }
                
                SwitchCaseSuccessors successors;
                successors.findUniqueBranches(inst);
                if (successors.numBranches() <= 1) {
                    // still an unconditional jump to the same successor block
                    return false;
                }
                
                const bool hasFallThroughCases = successors.hasFallThroughCases(block);
                u32 i = 0;
                if (!hasFallThroughCases) {
                    // for these successors, we can still use the raw onMultiBranch() API
                    for (BasicBlock* successor : successors.get()) {
                        traceMultiBranch(*successor, i++);
                    }
                } else {
                    // for these successors, we have to use the onSwitchCase() API
                    // with the bool flag used to ensure only one onMultiBranch() is called
                    Value& validPtr = successors.createValidPtr(inst);
                    for (BasicBlock* successor : successors.get()) {
                        traceSwitchCase(*successor, validPtr, i++);
                    }
                }
                
                return true;
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
                    .single = api.func<bool>("onSingleBranch"),
                    .multi = api.func<u32>("onMultiBranch"),
                    .switchCase = api.func<bool, u32>("onSwitchCase"),
                    .infinite = api.func<void*>("onInfiniteBranch"),
            };
            const FunctionCallee onFunctionStart = api.func<void*>("onFunctionStart");
            
            return filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        return BlockPass(flags, onBranch, block).trace();
                    }, [&](Function& function) {
                        IRBuilder<> builder(&*function.getEntryBlock().getFirstInsertionPt());
                        IRBuilderExt ext(builder);
                        ext.call(onFunctionStart, {&function});
                    });
        }
        
    };
    
    char BranchCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BranchCoveragePass>();
    
}
