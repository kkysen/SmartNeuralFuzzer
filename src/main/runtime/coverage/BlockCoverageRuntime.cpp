//
// Created by Khyber on 3/14/2019.
//

#include "BlockCoverageRuntime.h"

#include "src/main/runtime/coverage/include.h"

namespace runtime::coverage::block {
    
    class BlockCoverageRuntime {
    
    private:
        
        io::WriteBuffer<u64> buffer;
        
        u64 lastBlockNum = 0;
    
    public:
        
        void onBlock(u64 blockNum) noexcept {
            const u64 delta = math::difference(lastBlockNum, blockNum);
            lastBlockNum = blockNum;
            buffer << delta;
        }
        
        BlockCoverageRuntime() noexcept(false) : buffer(writer(output().dir.dir("block"), "blocks")) {}
        
    };
    
    thread_local auto& rt = LazilyConstructed<BlockCoverageRuntime>::add();
    
}

namespace {
    using runtime::coverage::block::rt;
}

API_BlockCoverage(onBlock)(u64 blockNum) noexcept {
//    printf("BlockCoverage: onBlock: %ld\n", blockNum);
    API_rt().onBlock(blockNum);
}
