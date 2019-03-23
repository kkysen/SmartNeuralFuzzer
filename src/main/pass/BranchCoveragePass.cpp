//
// Created by Khyber on 2/14/2019.
//

#include "src/share/common/numbers.h"
#include "src/share/llvm/LLVMArray.h"
#include "src/share/llvm/api.h"

namespace {
    
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
        
        bool doInitialization(Module& module) override {
            const Api api("BranchCoverage", module);
            onBranch = {
                    .single = api.func<bool>("onSingleBranch"),
                    .multi = api.func<u32, u32>("onMultiBranch"),
                    .infinite = api.func<void*>("onInfiniteBranch"),
            };
            return true;
        }
        
        bool doInitialization(Function& function) override {
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
        
        /**
         * Traces a getelementptr on the class pointer,
         * recording which (sub)class is resolved (and then a method on it dispatched).
         */
        bool traceDynamicClassDispatch(const GetElementPtrInst& getElementPtrInst) {
            // TODO
            return false;
        }
        
        /**
         * Traces a getelementptr on a raw function pointer.
         */
        bool traceDynamicFunctionDispatch(const GetElementPtrInst& getElementPtrInst) {
            // TODO
            return false;
        }
        
        /*
         * TODO class method and free function dynamic dispatch are actually totally different
         *
         * for class methods, I just need to record what class the object is
         * Ideally, this should be done as few times as possible when the object isn't changing
         * Hopefully, I can just emit the tracing call once and the rest is optimized out
         *      (Note: In general, this is an issue.
         *      Should I run my pass later so more optimizations have applied?
         *      Adding call instructions might disable many of those optimizations.
         *      The best case I think would to run all passes, then mine, then all of them again,
         *      but this will take twice as long. Maybe I can just run the major (inlining) ones  again.)
         *
         * for free functions, this will be done with getelementptr
         * I record the index and size of the array.
         * This doesn't work for class methods b/c the method is known (constant index), just not the class.
         */
        
        /**
         * Trace a dynamic dispatch, i.e. a function pointer call
         * computed from a getelementptr instruction.
         *
         * This calls onMultiBranch(index, size),
         * where index is the index of function pointer in the getelementptr instruction,
         * and size is the size of the array being indexed into.
         *
         * This takes the form of either a class or function dispatch (see above).
         */
        bool traceDynamicDispatch(const GetElementPtrInst& getElementPtrInst) {
            const auto& elementType = *getElementPtrInst.getResultElementType();
            // TODO the type should actually be a * or **
            if (elementType.isFunctionTy()) {
                return traceDynamicFunctionDispatch(getElementPtrInst);
            } else if (elementType.isFirstClassType()) {
                return traceDynamicClassDispatch(getElementPtrInst);
            } else {
                return false;
            }
        }
        
        bool traceDynamicDispatches(BasicBlock& block) {
            return std::any_of(block.begin(), block.end(), [this](auto& instruction) {
                const auto getElementPtrInst = dyn_cast<GetElementPtrInst>(&instruction);
                return getElementPtrInst && traceDynamicDispatch(*getElementPtrInst);
            });
        }
        
    };
    
}

char BranchCoveragePass::ID = 0;

static RegisterPass<BranchCoveragePass> branchCoveragePass("coverage.branch", "Branch Coverage Pass");
