//
// Created by Khyber on 3/14/2019.
//

#include "src/main/pass/coverage/includes.h"
#include "src/share/llvm/lib/conversions.h"
#include "src/share/llvm/debug.h"
#include "src/share/io/fse.h"

#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"

#include <numeric>
#include <fstream>

namespace llvm::pass::coverage::block {
    
    /**
      * Block Indices Source Map Format
      *
      * For every function, it is formatted as (using JS-style `` strings)
      * `\nfunction ${function}\n${function.blocks.map(block => `${block}`).join("\n")}`,
      * where `${function}` = `${function.name} at ${!function : "?:?" : `${fileName}:${lineNumber}`}`,
      * where `${function.name}` = demangled name w/ debug info or else raw name
      * where `${block}` = `\t${index}: ${block?.lineNumber}:${block?.columnNumber}}`,
      * where `${number}` = !number ? "?" : `${number}`,
      * where !function and !block are true if there's no debug info for them,
      * and where `${index}` is the global index of the block.
      */
    class BlockIndicesSourceMap {
    
    private:
        
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
        const DISubprogram* currentFunction = nullptr;
    
    public:
        
        void function(const Function& function) {
            hasDI = function.getSubprogram();
            out() << "\n" << "function ";
            if (!hasDI) {
                // can always default to raw name, which has to exist
                out() << function.getName() << " at " << "?:?";
            } else {
                const auto& di = *function.getSubprogram();
                currentFunction = &di;
                out() << di.getName() << " at " << getDIPath(di) << ":" << di.getLine();
            }
            out() << "\n";
        }
        
        void block(u64 index, const Instruction& instruction, bool entryBlock) {
            out() << "\t" << index << ": ";
            const bool instHasDI = instruction.getDebugLoc();
            if (!hasDI || (!instHasDI && !entryBlock)) {
                out() << "?:?";
            } else {
                if (entryBlock) {
                    const auto& di = *currentFunction;
                    out() << di.getLine() << ":" << "?";
                } else {
                    const auto& di = *instruction.getDebugLoc();
                    out() << di.getLine() << ":" << di.getColumn();
                }
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
            
            return filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        IRBuilder<> builder(&*block.getFirstInsertionPt());
                        IRBuilderExt ext(builder);
                        const auto& callInst = *ext.call(onBlock, {ext.constants().getInt(blockIndex)});
                        sourceMap.block(blockIndex, callInst, &block == &block.getParent()->front());
                        blockIndex++;
                        return true;
                    }, [&](Function& function) {
                        errs() << "Block: " << function.getName() << "\n";
                        sourceMap.function(function);
                    });
        }
        
    };
    
    char BlockCoveragePass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BlockCoveragePass>();
    
}
