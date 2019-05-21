//
// Created by Khyber on 3/14/2019.
//

#include "src/main/pass/coverage/includes.h"
#include "src/share/llvm/conversions.h"
#include "src/share/llvm/debug.h"

#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Support/raw_os_ostream.h"

#include <numeric>
#include <fstream>

namespace llvm::pass::coverage::block {
    
    namespace sourceMap {
        
        struct BlockIndex {
            
            u64 blockIndex;
            const DILocation* location;
            StringRef functionName;
            // functionName doesn't always exist,
            // but it usually does in another block in the same function
            
            constexpr BlockIndex(u64 blockIndex, const DILocation* location) noexcept
                    : blockIndex(blockIndex), location(location),
                      functionName(!location ? "" : location->getScope()->getName()) {}
            
            std::string path() const noexcept {
                using convert::view;
                // TODO fs::path::lexically_normal() should be used
                // since fs::canonical requires the path to exist and makes a bunch of syscalls
                // but it appears lexically_normal() isn't implemented in libstdc++ yet.
                return fs::canonical(fs::path()
                                     / view(location->getDirectory())
                                     / view(location->getFilename()))
                        .string();
            }
            
            constexpr u32 lineNumber() const noexcept {
                return location->getLine();
            }
            
            constexpr u32 columnNumber() const noexcept {
                return location->getColumn();
            }
            
            void print(raw_ostream& out) const {
                out << blockIndex << ": ";
                if (!location) {
                    out << "???";
                } else {
                    out << functionName << " at " << path()
                        << ":" << lineNumber() << ":" << columnNumber();
                }
            }
            
        };
        
        raw_ostream& operator<<(raw_ostream& out, const BlockIndex& rhs) {
            rhs.print(out);
            return out;
        }
        
        class FunctionBlocksIndex {
            
            SmallVector<BlockIndex, 0> blocks;
        
        public:
            
            void add(u64 blockIndex, const Instruction& instruction) {
                blocks.emplace_back(blockIndex, &*instruction.getDebugLoc());
            }
            
            void clearAndReserve(size_t size) {
                blocks.clear();
                blocks.reserve(size);
            }
            
            void fixFunctionNames() {
                const StringRef candidateFunctionName = blocks.back().functionName;
                const StringRef functionName = candidateFunctionName.empty() ? "???" : candidateFunctionName;
                for (auto& block : blocks) {
                    if (block.functionName.empty()) {
                        block.functionName = functionName;
                    }
                }
            }
            
            void print(raw_ostream& out) const {
                for (const auto& block : blocks) {
                    out << block << "\n";
                }
            }
            
        };
        
        raw_ostream& operator<<(raw_ostream& out, const FunctionBlocksIndex& rhs) {
            rhs.print(out);
            return out;
        }
        
    }
    
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

//            std::ofstream sourceMapFile;
//            raw_os_ostream sourceMapStream = sourceMapFile;
            raw_ostream& sourceMapStream = errs();
            
            sourceMap::FunctionBlocksIndex sourceMap;
            
            const auto& skipRuntimeFunctions = runtimeFunctionFilter();
            
            for (auto& function : module) {
                if (function.empty()) {
                    continue;
                }
                if (skipRuntimeFunctions(function)) {
                    continue;
                }
                errs() << "Block: " << function.getName() << "\n";
                sourceMap.clearAndReserve(function.size());
                for (auto& block : function) {
                    IRBuilder<> builder(&*block.getFirstInsertionPt());
                    IRBuilderExt ext(builder);
                    const auto& callInst = *ext.call(onBlock, {ext.constants().getInt(blockIndex)});
                    sourceMap.add(blockIndex, callInst);
                    blockIndex++;
                }
                sourceMap.fixFunctionNames();
                sourceMapStream << sourceMap << "\n";
            }
            return true;
        }
        
    };
    
    char BlockCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BlockCoveragePass>();
    
}
