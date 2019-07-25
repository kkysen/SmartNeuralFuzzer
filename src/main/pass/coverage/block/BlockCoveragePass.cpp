//
// Created by Khyber on 3/14/2019.
//

#include "src/main/pass/coverage/includes.h"
#include "src/share/llvm/lib/conversions.h"
#include "src/share/llvm/debug.h"
#include "src/share/io/fse.h"
#include "src/share/io/env/Argv.h"
#include "src/share/stde/compareEnds.h"

#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"

#include <numeric>
#include <fstream>

namespace {
    
    using env::Argv;
    using llvm::Module;
    
    std::string_view tryGetSourceMapNameFromArgv() {
        bool next = false;
        for (const auto& arg : Argv::get()) {
            if (arg == "-o") {
                next = true;
            } else if (next) {
                const std::string_view ext = ".0.6.coverage.";
                const auto i = arg.find(ext);
                if (i != std::string_view::npos) {
                    return arg.substr(0, i);
                }
                break;
            }
        }
        return {};
    }
    
    void getSourceMapName(const Module& module, fs::path& path) {
        const std::string_view argvName = tryGetSourceMapNameFromArgv();
        if (argvName.data()) {
            path = argvName;
        } else {
            path = module.getSourceFileName();
            path.replace_extension();
        }
    }
    
}

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
    class SourceMap {
    
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
                getSourceMapName(module, path);
                path += ".blocks.map";
            }
            
            raw_fd_ostream open() {
                return raw_fd_ostream(path.string(), ec);
            }
            
            void check() const {
                if (ec) {
                    fse::_throw(fs::filesystem_error("cannot open source map output", path, ec));
                }
            }
            
        };
        
        explicit SourceMap(Output output) : _out(output.open()) {
            output.check();
        }
    
    public:
        
        explicit SourceMap(const Module& module) : SourceMap(Output(module)) {}
    
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
        
        void function(u64 index, const Function& function) {
            hasDI = function.getSubprogram();
            out() << "\n" << index << ": ";
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
    
    class BlockCoveragePass : public NamedRegisteredPass<BlockCoveragePass> {
    
    public:
        
        static constexpr auto name = "Block Coverage Pass";
        
        bool runOnModule(Module& module) override {
            const Api api("BlockCoverage", module);
            FunctionCallee onFunction = api.func<void(u64)>("onFunction");
            FunctionCallee onBlock = api.func<void(u64)>("onBlock");
            u64 functionIndex = 0;
            u64 blockIndex = 0;
            
            SourceMap sourceMap(module);
            IRBuilderExt irbe(module);
            return filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
                        irbe.setInsertPoint(block, true);
                        const auto& callInst = irbe.callIndex(onBlock, blockIndex);
                        sourceMap.block(blockIndex, callInst, &block == &block.getParent()->front());
                        blockIndex++;
                        return true;
                    }, [&](Function& function) {
//                        errs() << "Block: " << function.getName() << "\n";
                        irbe.setInsertPoint(function, true);
                        irbe.callIndex(onFunction, functionIndex);
                        sourceMap.function(functionIndex, function);
                        functionIndex++;
                    });
        }
        
    };
    
    const bool registered = BlockCoveragePass::register_();
    
}
