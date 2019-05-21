//
// Created by Khyber on 3/14/2019.
//

#include <numeric>
#include <fstream>
#include "src/main/pass/coverage/includes.h"

namespace llvm::pass::coverage::block {
    
    class BlockCoveragePass : public ModulePass {
    
    public:
        
        static char ID;
        
        BlockCoveragePass() : ModulePass(ID) {}
        
        StringRef getPassName() const override {
            return "Block Coverage Pass";
        }
        
        using BlockDebugLocation = std::pair<u64, const DebugLoc&>;
        using BlockDebugLocations = SmallVector<BlockDebugLocation, 0>;
        
        static void saveBlockDebugLocations(const BlockDebugLocations&) {
//            std::ofstream out; // TODO what file
//            for (const auto[blockIndex, debugLoc] : blockDebugLocations) {
//                out << blockIndex << ": " << debugLoc << "\n";
//            }
        }
        
        bool runOnModule(Module& module) override {
            const Api api("BlockCoverage", module);
            FunctionCallee onBlock = api.func<u64>("onBlock");
            u64 blockIndex = 0;
            
            BlockDebugLocations blockDebugLocations;
            size_t numBlocks = std::accumulate(module.begin(), module.end(), 0, [](auto size, const auto& f) {
                return size + f.size();
            });
            blockDebugLocations.reserve(numBlocks);
            
            const auto f = [&onBlock, &blockIndex, &skipRuntimeFunctions = runtimeFunctionFilter(), &blockDebugLocations]
                    (Function& function) {
                if (function.empty()) {
                    return false;
                }
                if (skipRuntimeFunctions(function)) {
                    return false;
                }
                errs() << function.getName() << "\n";
                for (auto& block : function) {
                    IRBuilder<> builder(&*block.getFirstInsertionPt());
                    IRBuilderExt ext(builder);
                    const auto& callInst = *ext.call(onBlock, {ext.constants().getInt(blockIndex)});
                    const auto& debugLoc = callInst.getDebugLoc();
                    blockDebugLocations.emplace_back(blockIndex, debugLoc);
                    blockIndex++;
                }
                return true;
            };
            const bool modified = std::any_of(module.begin(), module.end(), f);
            if (modified) {
                saveBlockDebugLocations(blockDebugLocations);
            }
            return modified;
        }
        
    };
    
    char BlockCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BlockCoveragePass>();
    
}
