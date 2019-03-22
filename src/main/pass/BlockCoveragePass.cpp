//
// Created by Khyber on 3/14/2019.
//

#include "src/share/llvm/api.h"
#include "src/share/llvm/IRBuilderExt.h"

namespace {
    
    using namespace llvm;
    
    class BlockCoveragePass : public BasicBlockPass {
    
    private:
        
        FunctionCallee onBlock;
        u64 blockIndex = 0;
    
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
            IRBuilder<> builder(&block.front());
            IRBuilderExt ext(builder);
            ext.call(onBlock, {ext.constants().getInt(blockIndex)});
            blockIndex++;
            return true;
        }
        
    };
    
}

char BlockCoveragePass::ID = 0;

static RegisterPass<BlockCoveragePass> branchCoveragePass("coverage.block", "Block Coverage Pass");
