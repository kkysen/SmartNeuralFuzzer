//
// Created by Khyber on 3/14/2019.
//

#include "src/main/runtime/coverage/BlockCoverageRuntime.h"

#include "src/main/runtime/coverage/include.h"

#include <iostream>

namespace runtime::coverage::block {
    
    class BlockCoverageRuntime {
    
    private:
        
        class Buffer {
            
            io::LEB128WriteBuffer buffer;
            u64 lastIndex = 0;

        public:
            
            void on(u64 index) noexcept {
                const i64 delta = index - lastIndex;
                lastIndex = index;
                buffer << delta;
            }
            
            Buffer& operator<<(u64 index) noexcept {
                on(index);
                return *this;
            }
            
            Buffer(const fse::Dir& dir, const std::string& name) noexcept(false)
                    : buffer(writer(dir, name)) {}
            
        };
        
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
                : function(dir, "functions"), block(dir, "blocks") {}
    
    public:
        
        BlockCoverageRuntime() noexcept(false) : BlockCoverageRuntime(output().dir.dir("block")) {}
        
    };
    
    thread_local auto& rt = LazilyConstructed<BlockCoverageRuntime>::add();
    
}

namespace {
    using runtime::coverage::block::rt;
}

#define api API_BlockCoverage

void api(onFunction)(u64 functionIndex) noexcept {
//    printf("BlockCoverage: onFunction: %ld\n", functionNum);
    API_rt().onFunction(functionIndex);
}

void api(onBlock)(u64 blockIndex) noexcept {
//    printf("BlockCoverage: onBlock: %ld\n", blockNum);
    API_rt().onBlock(blockIndex);
}
