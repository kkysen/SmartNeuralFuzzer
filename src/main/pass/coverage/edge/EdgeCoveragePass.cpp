//
// Created by Khyber on 7/15/2019.
//

#include "src/main/pass/coverage/includes.h"

namespace {
    
    using namespace llvm;
    
    CallInst& call(BasicBlock& block, FunctionCallee f, u64 index) {
        IRBuilder<> irb(&*block.getFirstInsertionPt());
        IRBuilderExt irbe(irb);
        return irbe.callIndex(f, index);
    }
    
}

namespace llvm::pass::coverage::edge {
    
    class EdgeCoveragePass : public ModulePass {
    
    private:
        
        struct Api {
            const struct {
                const FunctionCallee front;
                const FunctionCallee back;
            } onEdge;
        };
        
        class InstructionPass {
        
        private:
            
            const Api& api;
            Instruction& instruction;
            u64 index;
            
            template <class InstType>
            constexpr InstType& getInst() const {
                return cast<InstType>(instruction);
            }
        
        public:
            
            constexpr InstructionPass(const Api& api, Instruction& instruction, u64 index) noexcept
                    : api(api), instruction(instruction), index(index) {}

        private:
            
            bool shouldTrace() {
                switch (instruction.getOpcode()) {
                    case Instruction::Br:
                        return getInst<BranchInst>().isConditional();
                    case Instruction::Switch:
                        return getInst<SwitchInst>().getNumCases() > 0;
                    case Instruction::Invoke:
                    case Instruction::CallBr:
                    case Instruction::Call:
                        return getInst<CallBase>().isIndirectCall();
                    case Instruction::IndirectBr: {
                        return getInst<IndirectBrInst>().getNumDestinations() > 0;
                    }
                    default:
                        return false;
                }
            }
            
        public:
            
            void trace() {
                if (shouldTrace()) {
                    IRBuilder<> irb(&instruction);
                    IRBuilderExt irbe(irb);
                    irbe.callIndex(api.onEdge.front, index);
                }
            }
            
            void operator()() {
                trace();
            }
            
        };
        
        class BlockPass {
        
        private:
            
            const Api& api;
            BasicBlock& block;
            u64 index;
        
        public:
            
            constexpr BlockPass(const Api& api, BasicBlock& block, u64 index) noexcept
                    : api(api), block(block), index(index) {}
            
            bool trace() {
                for (auto& inst : block) {
                    InstructionPass(api, inst, index)();
                }
                
                IRBuilder<> irb(&*block.getFirstInsertionPt());
                IRBuilderExt irbe(irb);
                irbe.callIndex(api.onEdge.back, index);
                
                return true;
            }
            
            bool operator()() {
                return trace();
            }
            
            
        };
    
    public:
        
        static char ID;
        
        EdgeCoveragePass() : ModulePass(ID) {}
        
        StringRef getPassName() const override {
            return "Edge Coverage Pass";
        }
        
        bool runOnModule(Module& module) override {
            using llvm::Api;
            const Api api("EdgeCoverage", module);
            const EdgeCoveragePass::Api ownApi = {
                    .onEdge = {
                            .front = api.func<void, u64>("onFrontEdge"),
                            .back = api.func<void, u64>("onBackEdge"),
                    },
            };
            u64 blockIndex = 0;
            return filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        return BlockPass(ownApi, block, blockIndex++)();
                    });
        }
        
    };
    
    char EdgeCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<EdgeCoveragePass>();
    
}
