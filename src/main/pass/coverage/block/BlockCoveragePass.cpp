//
// Created by Khyber on 3/14/2019.
//

#include <src/share/llvm/debug.h>
#include <src/main/pass/BinaryFunctionFilter.h>
#include "src/share/llvm/registerStandardPass.h"
#include "src/share/llvm/api.h"
#include "src/share/llvm/IRBuilderExt.h"

namespace llvm::pass::coverage::block {
    
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
            FunctionCallee onBlock = api.func<u64>("onBlock");
            u64 blockIndex = 0;
            BinaryFunctionFilter skipRuntimeFunctions;
            skipRuntimeFunctions.add(fs::path("src/main/runtime/coverage/block/libruntime.coverage.block.a")); // TODO
            const auto f = [&onBlock, &blockIndex](auto& function) {
                if (function.size() == 0) {
                    return false;
                }
//                if (skipRuntimeFunctions(function)) {
//                    return false;
//                }
                errs() << function.getName() << "\n";
                for (auto& block : function) {
                    IRBuilder<> builder(&*block.getFirstInsertionPt());
                    IRBuilderExt ext(builder);
                    ext.call(onBlock, {ext.constants().getInt(blockIndex)});
                    blockIndex++;
                }
                return true;
            };
            return std::any_of(module.begin(), module.end(), f);
        }
        
    };
    
    char BlockCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BlockCoveragePass>();
    
}
