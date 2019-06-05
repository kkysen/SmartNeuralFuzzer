//
// Created by Khyber on 3/14/2019.
//

#include "src/main/runtime/coverage/block/BlockCoverageRuntime.h"

#include "src/main/runtime/coverage/include.h"

namespace runtime::coverage::block {
    
    class BlockCoverageRuntime {
    
    private:
        
        io::WriteBuffer<u64> buffer;
    
    public:
        
        void onBlock(u64 blockNum) noexcept {
            buffer.on(blockNum);
        }
        
        BlockCoverageRuntime() noexcept(false) : buffer(writer(output().dir, "blocks")) {}
        
    };
    
    thread_local auto& rt = LazilyConstructed<BlockCoverageRuntime>::add();
    
}

namespace {
    using runtime::coverage::block::rt;
}

API_BlockCoverage(onBlock)(u64 blockNum) noexcept {
//    printf("BlockCoverage: onBlock: %ld\n", blockNum);
    rt().onBlock(blockNum);
}
