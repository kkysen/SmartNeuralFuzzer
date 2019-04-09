//
// Created by Khyber on 2/14/2019.
//

#include "src/share/llvm/debug.h"
#include "src/share/common/numbers.h"
#include "src/share/llvm/LLVMArray.h"
#include "src/share/llvm/api.h"
#include "src/share/llvm/registerStandardPass.h"

namespace pass::coverage::branch {
    
    using namespace llvm;
    
    class BranchCoveragePass : public BasicBlockPass {
    
    private:
        
        struct {
            FunctionCallee single;
            FunctionCallee multi;
            FunctionCallee infinite;
        } onBranch = {};
        
        struct Flags {
            bool branches;
            bool switches;
            bool virtualMethods;
        } flags {
                .branches = true,
                .switches = true,
                .virtualMethods = false,
        };
    
    public:
        
        static char ID;
        
        BranchCoveragePass() : BasicBlockPass(ID) {}
    
        StringRef getPassName() const override {
            return "Branch Coverage Pass";
        }
        
        bool doInitialization(Module& module) override {
            const Api api("BranchCoverage", module);
            onBranch = {
                    .single = api.func<bool>("onSingleBranch"),
                    .multi = api.func<u32, u32>("onMultiBranch"),
                    .infinite = api.func<void*>("onInfiniteBranch"),
            };
            return true;
        }
        
        bool doInitialization(Function&) override {
            // do nothing, but declaration needed for overload resolution?
            return false;
        }
        
        bool runOnBasicBlock(BasicBlock& block) override {
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
        
        void traceSwitchCase(const SwitchInst::CaseHandle& caseHandle, u32 caseNum, u32 numCases) {
            IRBuilder<> builder(&caseHandle.getCaseSuccessor()->front());
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
            
            // insert tracing code into each BasicBlock for each case
            auto i = 0u;
            traceSwitchCase(*switchInst.case_default(), i++, numCases);
            for (const auto& caseHandle : switchInst.cases()) {
                traceSwitchCase(caseHandle, i++, numCases);
            }
            return true;
        }
        
        bool traceDynamicDispatches([[maybe_unused]] BasicBlock& block) {
            return true;
        }
        
    };
    
    char BranchCoveragePass::ID = 0;
    
//    RegisterPass<BranchCoveragePass> pass("coverage.branch", "Branch Coverage Pass");
    
    bool registered = llvm::pass::registerStandardAlwaysLast<BranchCoveragePass>();
    
}
