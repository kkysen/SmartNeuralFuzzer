//
// Created by Khyber on 3/14/2019.
//

#include "src/share/llvm/registerStandardPass.h"
#include "src/share/llvm/api.h"
#include "src/share/llvm/IRBuilderExt.h"

namespace pass::coverage::block {
    
    using namespace llvm;
    
    class BlockCoveragePass : public ModulePass {
    
    public:
        
        static char ID;
        
        BlockCoveragePass() : ModulePass(ID) {}
        
        StringRef getPassName() const override {
            return "Block Coverage Pass";
        }
        
        bool runOnModule(Module& module) override {
            const Api api("BlockCoverage", module);
            const FunctionCallee onBlock = api.func<u64>("onBlock");
            u64 blockIndex = 0;
            for (auto& function : module) {
                for (auto& block : function) {
                    IRBuilder<> builder(&*block.getFirstInsertionPt());
                    IRBuilderExt ext(builder);
                    ext.call(onBlock, {ext.constants().getInt(blockIndex)});
                    blockIndex++;
                }
            }
            return true;
        }
        
    };
    
    char BlockCoveragePass::ID = 0;
    
//    RegisterPass<BlockCoveragePass> pass("coverage.block", "Block Coverage Pass");
    
    bool registered = llvm::pass::registerStandardAlwaysLast<BlockCoveragePass>();
    
}
