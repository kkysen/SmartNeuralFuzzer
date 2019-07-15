//
// Created by Khyber on 6/24/2019.
//

#include "src/main/pass/coverage/includes.h"

#include "llvm/IR/CFG.h"

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
            const Instruction& instruction;
            IRBuilder<>& irb;
            IRBuilderExt irbe;
        
        public:
            
            constexpr InstructionPass(const Api& api, const Instruction& instruction, IRBuilder<>& irb) noexcept
                    : api(api), instruction(instruction), irb(irb), irbe(irb) {}
            
        private:
    
            void transformBranch(const BranchInst& inst) {
        
            }
    
            void transformSwitch(const SwitchInst& inst) {
        
            }
    
            void transformIndirectCall(const CallBase& inst) {
        
            }
    
            template <class InstType>
            bool tryTransform(void (InstructionPass::*f)(const InstType&)) {
                const bool transformed = isa<InstType>(instruction);
                if (transformed) {
                    (this->*f)(cast<InstType>(instruction));
                }
                return transformed;
            }

        public:
    
            void transform() {
                using This = InstructionPass;
                if (tryTransform(&This::transformBranch)) {}
                else if (tryTransform(&This::transformSwitch)) {}
                else if (tryTransform(&This::transformIndirectCall)) {}
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
                for (const auto& inst : block.original) {
                    InstructionPass(api, inst, irb)();
                }
                return true;
            }
            
            bool operator()() {
                return transform();
            }
        
        private:
            
            bool traceCondition(Instruction& inst, Value* conditionPtr) const {
                if (!conditionPtr) {
                    return false;
                }
                auto& condition = *conditionPtr;
                IRBuilder<> builder(&inst);
                IRBuilderExt ext(builder);
                ext.call(nextBranch.single, {&condition});
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
                ext.call(nextBranch.infinite);
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
                ext.call(nextBranch.multi, {&constants.getInt(branchNum), &constants.getInt(numBranches)});
            }
            
            void traceSwitchCase(BasicBlock& block, Value& validPtr, u64 caseNum, u64 numCases) const {
                IRBuilder<> builder(&block.front());
                IRBuilderExt ext(builder);
                const auto constants = ext.constants();
                Value* valid = builder.CreateLoad(&validPtr);
                ext.call(nextBranch.switchCase, {valid, &constants.getInt(caseNum), &constants.getInt(numCases)});
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
