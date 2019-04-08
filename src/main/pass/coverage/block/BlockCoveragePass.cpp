//
// Created by Khyber on 3/14/2019.
//

#include "src/share/llvm/registerStandardPass.h"
#include "src/share/llvm/api.h"
#include "src/share/llvm/IRBuilderExt.h"

namespace pass::coverage::block {
    
    using namespace llvm;
    
    class BlockCoveragePass : public BasicBlockPass {
    
    private:
        
        FunctionCallee onBlock;
        u64 blockIndex = 0;
    
    public:
        
        static char ID;
        
        BlockCoveragePass() : BasicBlockPass(ID) {}
        
        bool doInitialization(Module& module) override {
            const Api api("BlockCoverage", module);
            onBlock = api.func<u64>("onBlock");
            return true;
        }
        
        bool doInitialization(Function&) override {
            // do nothing, but declaration needed for overload resolution?
            return false;
        }
        
        bool runOnBasicBlock(BasicBlock& block) override {
            llvm_dbg(blockIndex);
            IRBuilder<> builder(&*block.getFirstInsertionPt());
            IRBuilderExt ext(builder);
            ext.call(onBlock, {ext.constants().getInt(blockIndex)});
            blockIndex++;
            return true;
        }
        
    };
    
    char BlockCoveragePass::ID = 0;
    
    void registerPass(const PassManagerBuilder&, legacy::PassManagerBase& pm) {
        pm.add(new BlockCoveragePass());
    }
    
}

using pass::coverage::block::BlockCoveragePass;
using pass::coverage::block::registerPass;
using llvm::RegisterStandardPasses;
using llvm::PassManagerBuilder;

//static llvm::RegisterPass<BlockCoveragePass> blockCoveragePass("coverage.block", "Block Coverage Pass");

static RegisterStandardPasses registerBlockCoveragePass(PassManagerBuilder::EP_OptimizerLast, registerPass);

static RegisterStandardPasses registerBlockCoveragePass0(PassManagerBuilder::EP_EnabledOnOptLevel0, registerPass);

//bool registered = llvm::pass::registerStandardAlwaysLast<BlockCoveragePass>();
