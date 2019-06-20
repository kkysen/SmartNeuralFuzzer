//
// Created by Khyber on 2/14/2019.
//

#include <src/share/llvm/debug.h>
#include "src/main/pass/coverage/includes.h"

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
            
            void traceSwitchCase(BasicBlock* blockPtr, u32 caseNum, u32 numCases) {
                IRBuilder<> builder(blockPtr);
                IRBuilderExt ext(builder);
                const auto constants = ext.constants();
                ext.call(onBranch.multi, {constants.getInt(caseNum), constants.getInt(numCases)});
            }
            
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
                
                // each branch can have multiple cases
                // i.e., multiple cases can go to the same successor block,
                // but it's only 1 real branch in that case
                
                SmallPtrSet<BasicBlock*, 8> successors;
                successors.insert(switchInst.case_default()->getCaseSuccessor());
                for (const auto& caseHandle : switchInst.cases()) {
                    successors.insert(caseHandle.getCaseSuccessor());
                }
                successors.erase(nullptr);
                
                const auto numBranches = successors.size();
                if (numBranches <= 1) {
                    // still an unconditional jump to the same successor block
                    return false;
                }
                
                llvm_dbg(std::pair(numBranches, numCases));

                // insert tracing code into each successor BasicBlock for each branch
                auto i = 0u;
                for (auto* successor : successors) {
                    traceSwitchCase(successor, i++, numBranches);
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
                    .infinite = api.func<void*>("onInfiniteBranch"),
            };
            
            return filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        return BlockPass(flags, onBranch, block).trace();
                    }, [](Function&) {
//                        errs() << "Branch: " << function.getName() << "\n";
                    });
        }
        
    };
    
    char BranchCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BranchCoveragePass>();
    
}
