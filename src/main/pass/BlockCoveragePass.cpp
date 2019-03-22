//
// Created by Khyber on 3/14/2019.
//

#include "src/share/llvm/api.h"
#include "src/share/common/numbers.h"

namespace {
    
    using namespace llvm;
    
    class BlockCoveragePass : public BasicBlockPass {
    
    private:
        
        FunctionCallee onBlock;
    
    public:
        
        static char ID;
        
        BlockCoveragePass() : BasicBlockPass(ID) {}
        
        bool doInitialization(Module& module) override {
            Api api("BlockCoverage", module);
            onBlock = api.func<u32>("onBlock");
            return true;
        }
        
        bool doInitialization(Function& function) override {
            // do nothing, but declaration needed for overload resolution?
            return false;
        }
        
        bool runOnBasicBlock(BasicBlock& block) override {
            return false;
        }
        
    };
    
}

char BlockCoveragePass::ID = 0;

static RegisterPass<BlockCoveragePass> branchCoveragePass("coverage.block", "Block Coverage Pass");
