//
// Created by Khyber on 3/14/2019.
//

#include "src/main/runtime/coverage/BlockCoverageRuntime.h"

#include "src/main/runtime/coverage/include.h"
#include "src/share/io/DeltaWriteBuffer.h"

namespace runtime::coverage::block {
    
    class BlockCoverageRuntime {
    
    private:
        
        using Buffer = io::DeltaWriteBuffer<io::LEB128WriteBuffer>;
        
        Buffer function;
        Buffer block;
    
    public:
        
        void onFunction(u64 functionIndex) noexcept {
            function << functionIndex;
        }
        
        void onBlock(u64 blockIndex) noexcept {
            block << blockIndex;
        }
    
    private:
        
        explicit BlockCoverageRuntime(const fse::Dir& dir) noexcept(false)
                : function(writer(dir, "functions")),
                  block(writer(dir, "blocks")) {}
    
    public:
        
        BlockCoverageRuntime() noexcept(false) : BlockCoverageRuntime(output().dir.dir("block")) {}
        
    };
    
    thread_local auto& rt = LazilyConstructed<BlockCoverageRuntime>::add();
    
}

namespace {
    using runtime::coverage::block::rt;
}

#define api API_BlockCoverage

void api (onFunction)(u64 functionIndex) noexcept {
//    printf("BlockCoverage: onFunction: %ld\n", functionIndex);
    API_rt().onFunction(functionIndex);
}

void api (onBlock)(u64 blockIndex) noexcept {
//            printf("BlockCoverage: onBlock: %ld\n", blockIndex);
    API_rt().onBlock(blockIndex);
}
