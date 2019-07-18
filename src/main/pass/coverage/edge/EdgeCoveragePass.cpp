//
// Created by Khyber on 7/15/2019.
//

#include "src/main/pass/coverage/includes.h"

#include "llvm/IR/CFG.h"

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
            IRBuilderExt& irbe;
            u64 index;
            
            template <class InstType>
            constexpr InstType& getInst() const {
                return cast<InstType>(instruction);
            }
        
        public:
            
            constexpr InstructionPass(const Api& api, Instruction& instruction, IRBuilderExt& irbe, u64 index) noexcept
                    : api(api), instruction(instruction), irbe(irbe), index(index) {}
        
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
                    case Instruction::IndirectBr:
                        return getInst<IndirectBrInst>().getNumDestinations() > 0;
                    default:
                        return false;
                }
            }
        
        public:
            
            bool trace() {
                const bool traced = shouldTrace();
                if (traced) {
                    irbe.setInsertPoint(instruction);
                    irbe.callIndex(api.onEdge.front, index);
                }
                return traced;
            }
            
            bool operator()() {
                return trace();
            }
            
        };
        
        class BlockPass {
        
        private:
            
            const Api& api;
            BasicBlock& block;
            IRBuilderExt& irbe;
            u64 index;
        
        public:
            
            constexpr BlockPass(const Api& api, BasicBlock& block, IRBuilderExt& irbe, u64 index) noexcept
                    : api(api), block(block), irbe(irbe), index(index) {}
        
        private:
            
            constexpr bool isEntryBlock() const noexcept {
                return &block == &block.getParent()->getEntryBlock();
            }
            
            constexpr bool isFrontEdge(const Instruction& inst) const noexcept {
                switch (inst.getOpcode()) {
                    case Instruction::Br:
                        return cast<BranchInst>(inst).isConditional();
                    case Instruction::Switch:
                        return cast<SwitchInst>(inst).getNumCases() > 0;
                    case Instruction::IndirectBr:
                        return cast<IndirectBrInst>(inst).getNumDestinations() > 0;
                }
                return false;
            }
            
            constexpr bool isFrontEdge(const BasicBlock& block) const noexcept {
                return block.getTerminator() && isFrontEdge(*block.getTerminator());
            }
    
            bool predecessorIsFrontEdge() const noexcept {
                for (auto* const predecessor : llvm::predecessors(&block)) {
                    if (isFrontEdge(*predecessor)) {
                        return true;
                    }
                }
                return false;
            }
            
            bool isBackEdge() const noexcept {
                return isEntryBlock() || predecessorIsFrontEdge();
            }
            
            void traceBackEdge() {
                irbe.setInsertPoint(block, true);
                irbe.callIndex(api.onEdge.back, index);
            }
        
        public:
            
            bool trace() {
                bool traced = false;
                for (auto& inst : block) {
                    traced |= InstructionPass(api, inst, irbe, index)();
                }
                if (isBackEdge()) {
                    traceBackEdge();
                    traced = true;
                }
                return traced;
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
                            .front = api.func<void(u64)>("onFrontEdge"),
                            .back = api.func<void(u64)>("onBackEdge"),
                    },
            };
            IRBuilderExt irbe(module);
            u64 blockIndex = 0;
            return filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        return BlockPass(ownApi, block, irbe, blockIndex++)();
                    });
        }
        
    };
    
    char EdgeCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<EdgeCoveragePass>();
    
}
