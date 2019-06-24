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
            bool virtualMethods;
        } flags {
                .branches = true,
                .switches = true,
                .virtualMethods = false,
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
                const auto terminator = block.getTerminator();
                if (!terminator) {
                    return false;
                }
                bool traced = false;
                if (const auto branchInst = dyn_cast<BranchInst>(terminator)) {
                    traced |= flags.branches && traceBranch(*branchInst);
                } else if (const auto switchInst = dyn_cast<SwitchInst>(terminator)) {
                    traced |= flags.switches && traceSwitch(*switchInst);
                }
//            traced |= flags.virtualMethods && traceDynamicDispatches(block);
                return traced;
            }
        
        private:
            
            /**
             * Trace a br (branch) instruction
             * by calling onBranch(booleanValue) immediately before the branch.
             */
            bool traceBranch(BranchInst& branchInst) {
                if (!branchInst.isConditional()) {
                    return false;
                }
                IRBuilder<> builder(&branchInst);
                IRBuilderExt ext(builder);
                ext.call(onBranch.single, {branchInst.getCondition()});
                return true;
            }
            
            void traceMultiBranch(BasicBlock& block, u32 branchNum, u32 numBranches) {
                IRBuilder<> builder(&block.front());
                IRBuilderExt ext(builder);
                const auto constants = ext.constants();
                ext.call(onBranch.multi, {constants.getInt(branchNum), constants.getInt(numBranches)});
            }
            
            void traceSwitchCase(BasicBlock& block, Value& validPtr, u32 caseNum, u32 numCases) {
                IRBuilder<> builder(&block.front());
                IRBuilderExt ext(builder);
                const auto constants = ext.constants();
                Value* valid = builder.CreateLoad(&validPtr);
                ext.call(onBranch.switchCase, {valid, constants.getInt(caseNum), constants.getInt(numCases)});
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
                    IRBuilder<> builder(&switchInst);
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
            bool traceSwitch(SwitchInst& switchInst) {
                const auto numCases = switchInst.getNumCases() + 1;
                if (numCases <= 1) {
                    // unconditionally jump to default case
                    return false;
                }
                
                SwitchCaseSuccessors successors;
                successors.findUniqueBranches(switchInst);
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
                    Value& validPtr = successors.createValidPtr(switchInst);
                    for (BasicBlock* successor : successors.get()) {
                        traceSwitchCase(*successor, validPtr, i++, numBranches);
                    }
                }
                
                return true;
            }
            
            bool traceDynamicDispatches([[maybe_unused]] BasicBlock& _block) {
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
                    .multi = api.func<u32, u32>("onMultiBranch"),
                    .switchCase = api.func<bool, u32, u32>("onSwitchCase"),
                    .infinite = api.func<void*>("onInfiniteBranch"),
            };
            
            return filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        return BlockPass(flags, onBranch, block).trace();
                    });
        }
        
    };
    
    char BranchCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BranchCoveragePass>();
    
}
