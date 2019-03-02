//
// Created by Khyber on 2/14/2019.
//

#include "llvm/Pass.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "numbers.h"
#include "LLVMArray.h"
#include "debug.h"

void __BranchCoverage_onBranch(bool value);

void __BranchCoverage_onMultiBranch(u32 branchNum, u32 numBranches);

void __BranchCoverage_onInfiniteBranch(u64 address);

//void __BranchCoverage_onMultiBranch(u64 bits, u16 numBits);

namespace {
    
    using namespace llvm;
    
    class BranchCoveragePass : public BasicBlockPass {
    
    private:
        
        // TODO initialize
        FunctionCallee onBranch;
        FunctionCallee onMultiBranch;
        FunctionCallee onInfiniteBranch;
        
        struct Flags {
            bool branches;
            bool switches;
            bool virtualMethods;
        } flags {
            .branches = true,
            .switches = false,
            .virtualMethods = false,
        };
        
    public:
    
        static char ID;
        
        BranchCoveragePass() : BasicBlockPass(ID) {}
        
        template <typename... Args>
        FunctionCallee api(Module& module, std::string_view name) {
            std::string apiName = "__BranchCoverage_";
            apiName += name;
            const Types types(module.getContext());
            auto functionType = types.function<void, Args...>();
            llvm_dbg(functionType);
            auto callee = module.getOrInsertFunction(apiName, functionType);
            
            /**
             * TODO FIXME
             * This is causing an error because I thought I was using the newer git version of llvm
             * in which module.getOrInsertFunction returns a FunctionCallee,
             * but I'm actually using the older svn version,
             * in which module.getOrInsertFunction returns a Constant*.
             *
             * Now I have to actually compile the newer version.
             */
            
            llvm_dbg(!!callee);
            llvm_dbg(callee.getFunctionType() == nullptr);
            llvm_dbg(callee.getCallee() == nullptr);
            llvm_dbg(functionType == callee.getFunctionType());
            llvm_dbg(reinterpret_cast<uintptr_t>(functionType));
            llvm_dbg(reinterpret_cast<uintptr_t>(callee.getFunctionType()));
            llvm_dbg(callee.getFunctionType());
            llvm_dbg(callee.getFunctionType()->getNumParams());
            for (auto& param : callee.getFunctionType()->params()) {
                llvm_dbg(param);
            }
            return callee;
        }
        
        bool doInitialization(Module& module) override {
            const Types types(module.getContext());
//            onBranch = module.getOrInsertFunction("__BranchCoveragePass_onBranch", types.get<void>(), types.get<bool>());
            onBranch = api<bool>(module, "onBranch");
            onMultiBranch = api<u32, u32>(module, "onMultiBranch");
            onInfiniteBranch = api<u64>(module, "onInfiniteBranch");
            
            llvm_dbg(onBranch.getFunctionType());
            
            // TODO figure out where main is and check if blocks are below/after main before tracing them
            return true;
        }
        
        bool doInitialization(Function& function) override {
            // do nothing, but declaration needed for overload resolution?
            return false;
        }
        
        bool runOnBasicBlock(BasicBlock& block) override {
            const auto terminator = block.getTerminator();
            llvm_dbg(llvm::uuid(block));
            if (!(terminator && terminator->getPrevNode())) {
                llvm_debug().message("skipping empty block");
                return false;
            }
            IRBuilder<> builder(terminator->getPrevNode());
            IRBuilderExt ext(builder);
            bool traced = false;
            if (const auto branchInst = dyn_cast<BranchInst>(terminator)) {
                llvm_debug().message("tracing branch");
                traced |= flags.branches && traceBranch(*branchInst, ext);
            } else if (const auto switchInst = dyn_cast<SwitchInst>(terminator)) {
                llvm_debug().message("tracing switch");
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
        /*constexpr*/ bool traceBranch(BranchInst& branchInst, IRBuilderExt& ext) {
            llvm_dbg(branchInst);
            if (!branchInst.isConditional()) {
                return false;
            }
            llvm_debug().message("conditional");
            llvm_dbg(onBranch.getFunctionType());
            ext.call(onBranch, {branchInst.getCondition()});
            return true;
        }
        
        void traceSwitchCase(const SwitchInst::CaseHandle& caseHandle, u32 caseNum, u32 numCases) {
            IRBuilder<> builder(&caseHandle.getCaseSuccessor()->front());
            IRBuilderExt ext(builder);
            const auto constants = ext.constants();
            ext.call(onMultiBranch, {constants.getInt(caseNum), constants.getInt(caseNum)});
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
            if (block.size()) {
                return false;
            }
            return std::any_of(block.begin(), block.end(), [this](auto& instruction) {
                const auto getElementPtrInst = dyn_cast<GetElementPtrInst>(&instruction);
                return getElementPtrInst && traceDynamicDispatch(*getElementPtrInst);
            });
        }
        
    };
    
}

char BranchCoveragePass::ID = 0;

static RegisterPass<BranchCoveragePass> branchCoveragePass("branch-coverage", "Branch Coverage Pass");