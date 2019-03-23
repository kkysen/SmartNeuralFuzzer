//
// Created by Khyber on 3/14/2019.
//

#include "src/main/runtime/BlockCoverageRuntime.h"

#include "src/share/common/lazy.h"
#include "src/share/io/Buffer.h"
#include "src/share/io/EnvironmentOutputPath.h"

namespace {
    
    class BlockCoverageRuntime {
    
    private:
        
        Buffer<u64> buffer;
    
    public:
        
        explicit constexpr BlockCoverageRuntime(Write&& write) noexcept : buffer(std::move(write)) {}
        
        void onBlock(u64 blockNum) noexcept {
            buffer.on(blockNum);
        }
    
    private:
        
        static constexpr auto getOutputPath = env::path::output::getter(
                [](const auto& var, auto pid) -> fs::path { return var + "." + std::to_string(pid) + ".bin"; });
        
        static int createOutput(const fs::path& path) {
            const int fd = creat(path.c_str(), 0644);
            if (fd == -1) {
                throw fse::error("creat", path);
            }
            return fd;
        }
    
    public:
        
        explicit BlockCoverageRuntime(const std::string& environmentVariableName = "coverage.block.out")
                : BlockCoverageRuntime(Write(createOutput(getOutputPath(environmentVariableName)))) {}
        
        static const LazilyConstructed<BlockCoverageRuntime> instance;
        
    };
    
    const LazilyConstructed<BlockCoverageRuntime> BlockCoverageRuntime::instance;
    
    auto& runtime = BlockCoverageRuntime::instance;
    
}

API_BlockCoverage(onBlock)(u64 blockNum) {
//    printf("BlockCoverage: onBlock: %ld\n", blockNum);
    runtime().onBlock(blockNum);
}
