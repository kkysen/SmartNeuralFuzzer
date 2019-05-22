//
// Created by Khyber on 3/14/2019.
//

#include "src/main/pass/coverage/includes.h"
#include "src/share/llvm/conversions.h"
#include "src/share/llvm/debug.h"

#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"

#include <numeric>
#include <fstream>
#include <src/share/io/fse.h>

namespace llvm::pass::coverage::block {
    
    /**
      * Block Indices Source Map Format
      *
      * For every function, it is formatted as (using JS-style `` strings)
      * `\nfunction ${function}\n${blocks.map(block => `${block}`).join("\n")}`,
      * where `${function}` = !function ? "???" : `${functionName} at ${fileName}:${lineNumber}`,
      * and where `${block}` = `\t${index}: ${!block ? "???" : `${lineNumber}:${columnNumber}`}`,
      * where !function and !block are true if there's no debug info for them,
      * and where `${index}` is the global index of the block.
      */
    class BlockIndicesSourceMap {
    
    private:
        
        static std::string getDIPath(const DIScope& di) {
            using convert::view;
            // TODO fs::path::lexically_normal() should be used
            // since fs::canonical requires the path to exist and makes a bunch of syscalls
            // but it appears lexically_normal() isn't implemented in libstdc++ yet.
            return fs::canonical(fs::path()
                                 / view(di.getDirectory())
                                 / view(di.getFilename()))
                    .string();
        }
        
        bool hasDI = true;
        raw_fd_ostream _out;
        
        constexpr raw_ostream& out() noexcept {
            return _out;
        }
        
        class Output {

        private:
            
            std::error_code ec;
            
        public:
    
            fs::path path;
            
            explicit Output(const Module& module) {
                path = module.getSourceFileName();
                path += ".blocks.map";
            }
            
            raw_fd_ostream open() {
                // TODO I realize I could've used LLVM's fs code, but I like my own better.
                return raw_fd_ostream(path.string(), ec);
            }
            
            void check() const {
                if (ec) {
                    fse::_throw(fs::filesystem_error("cannot open source map output", path, ec));
                }
            }
            
        };
        
        explicit BlockIndicesSourceMap(Output output) : _out(output.open()) {
            output.check();
        }
    
    public:
        
        explicit BlockIndicesSourceMap(const Module& module) : BlockIndicesSourceMap(Output(module)) {}
        
        void function(const Function& function) {
            hasDI = function.getSubprogram();
            out() << "\n" << "function ";
            if (!hasDI) {
                out() << "???";
            } else {
                const auto& di = *function.getSubprogram();
                out() << di.getName() << " at " << getDIPath(di) << ":" << di.getLine();
            }
            out() << "\n";
        }
        
        void block(u64 index, const Instruction& instruction) {
            out() << "\t" << index << ": ";
            if (!hasDI || !instruction.getDebugLoc()) {
                out() << "???";
            } else {
                const auto& di = *instruction.getDebugLoc();
                out() << di.getLine() << ":" << di.getColumn();
            }
            out() << "\n";
        }
        
    };
    
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
            
            BlockIndicesSourceMap sourceMap(module);
            const auto& skipRuntimeFunctions = runtimeFunctionFilter();
            
            for (auto& function : module) {
                if (function.empty()) {
                    continue;
                }
                if (skipRuntimeFunctions(function)) {
                    continue;
                }
                errs() << "Block: " << function.getName() << "\n";
                sourceMap.function(function);
                for (auto& block : function) {
                    IRBuilder<> builder(&*block.getFirstInsertionPt());
                    IRBuilderExt ext(builder);
                    const auto& callInst = *ext.call(onBlock, {ext.constants().getInt(blockIndex)});
                    sourceMap.block(blockIndex, callInst);
                    blockIndex++;
                }
            }
            
            return true;
        }
        
    };
    
    char BlockCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BlockCoveragePass>();
    
}
