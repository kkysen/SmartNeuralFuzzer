//
// Created by Khyber on 3/14/2019.
//

#include "src/main/runtime/coverage/EdgeCoverageRuntime.h"

#include "src/main/runtime/coverage/include.h"
#include "src/share/io/DeltaWriteBuffer.h"

namespace {
    
    // implemented outside of EdgeCoverageRuntime class
    // since I have to check if the class is created first
    // but checking this boolean first is faster
    thread_local bool pendingBackEdge = false;
    
}

namespace runtime::coverage::block {
    
    class EdgeCoverageRuntime {
    
    private:
        
        using Buffer = io::DeltaWriteBuffer<io::LEB128WriteBuffer>;
        
        Buffer edge;
    
    public:
        
        void onFrontEdge(u64 blockIndex) noexcept {
            pendingBackEdge = true;
            edge << blockIndex;
        }
    
        void onBackEdge(u64 blockIndex) noexcept {
            pendingBackEdge = false;
            edge << blockIndex;
        }

    public:
        
        explicit EdgeCoverageRuntime() noexcept(false)
                : edge(writer(output().dir, "edges")) {}
        
    };
    
    thread_local auto& rt = LazilyConstructed<EdgeCoverageRuntime>::add();
    
}

namespace {
    using runtime::coverage::block::rt;
}

#define api API_EdgeCoverage

void api (onFrontEdge)(u64 blockIndex) noexcept {
    API_rt().onFrontEdge(blockIndex);
}

void api (onBackEdge)(u64 blockIndex) noexcept {
    if (pendingBackEdge) {
        API_rt().onBackEdge(blockIndex);
    }
}
