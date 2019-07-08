//
// Created by Khyber on 6/24/2019.
//

#include "src/main/runtime/coverage/BranchExecutionRuntime.h"

#include "src/share/io/BoolReader.h"
#include "src/share/io/LEB128Reader.h"
#include "src/share/io/DeltaWriteBuffer.h"
#include "src/share/common/lazy.h"

namespace runtime::coverage::branch::execute {
    
    struct Edge {
        // block indices
        u64 start;
        u64 end;
    };
    
    io::DeltaWriteBuffer& operator<<(io::DeltaWriteBuffer& out, const Edge& edge) {
        return out << edge.start << edge.end;
    }
    
    std::ostream& operator<<(std::ostream& out, const Edge& edge) {
        return out << edge.start << ':' << edge.end << '\n';
    }
    
    struct Output {
        
        io::DeltaWriteBuffer raw;
        std::ostream& formatted;
        const bool format;
        
        Output& operator<<(const Edge& edge) {
            if (format) {
                formatted << edge;
            } else {
                raw << edge;
            }
            return *this;
        }
        
    };
    
    class SingleBranches {
    
    private:
        
        io::BoolReader reader;
    
    public:
        
        constexpr bool next() noexcept {
            return reader.next();
        }
        
    };
    
    class NonSingleBranches {
    
    private:
        
        io::LEB128Reader reader;
        
        constexpr u64 next() noexcept {
            return reader.next<u64>();
        }
    
    public:
        
        constexpr u32 nextMulti() noexcept {
            return static_cast<u32>(next());
        }
        
        void* nextInfinite() noexcept {
            return reinterpret_cast<void*>(next());
        }
        
    };
    
    struct Branches {
        
        SingleBranches single;
        NonSingleBranches nonSingle;
        
    };
    
    class BranchExecutionRuntime {
    
    private:
        
        Branches branches;
        Output output;
    
    public:
        
        bool nextSingleBranch() noexcept {
            return branches.single.next();
        }
        
        u32 nextMultiBranch() noexcept {
            return branches.nonSingle.nextMulti();
        }
        
        void* nextInfiniteBranch() noexcept {
            return branches.nonSingle.nextInfinite();
        }
        
        void onEdge(u64 startBlockIndex, u64 endBlockIndex) noexcept {
            output << Edge {.start = startBlockIndex, .end = endBlockIndex};
        }
        
    };
    
    auto rt = LazilyConstructed<BranchExecutionRuntime>();
    
}

namespace {
    using runtime::coverage::branch::execute::rt;
}

#define api API_BranchExecution

bool api (nextSingleBranch)() noexcept {
    return rt().nextSingleBranch();
}

u32 api (nextMultiBranch)() noexcept {
    return rt().nextMultiBranch();
}

void* api(nextInfiniteBranch)() noexcept {
    return rt().nextInfiniteBranch();
}

void api (onEdge)(u64 startBlockIndex, u64 endBlockIndex) noexcept {
    //    printf("BranchExecution: onEdge: %lu, %lu\n", startBlockIndex, endBlockIndex);
    rt().onEdge(startBlockIndex, endBlockIndex);
}
