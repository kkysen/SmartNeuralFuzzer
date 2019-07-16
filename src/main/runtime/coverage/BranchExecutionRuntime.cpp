//
// Created by Khyber on 6/24/2019.
//

#include "src/main/runtime/coverage/BranchExecutionRuntime.h"

#include "src/share/io/BitReader.h"
#include "src/share/io/LEB128Reader.h"
#include "src/share/io/DeltaWriteBuffer.h"
#include "src/share/common/lazy.h"
#include "src/main/runtime/coverage/CoverageOutput.h"

#include <iostream>

namespace runtime::coverage::branch::execute {
    
    struct Edge {
        // block indices
        u64 start;
        u64 end;
    };
    
    using WriteBuffer = io::DeltaWriteBuffer<io::LEB128WriteBuffer>;
    
    WriteBuffer& operator<<(WriteBuffer& out, const Edge& edge) {
        return out << edge.start << edge.end;
    }
    
    std::ostream& operator<<(std::ostream& out, const Edge& edge) {
        return out << edge.start << ':' << edge.end << '\n';
    }
    
    struct Output {
        
        WriteBuffer raw;
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
        
        constexpr Output(io::Writer&& writer, std::ostream& formatted, bool format) noexcept
                : raw(std::move(writer)), formatted(formatted), format(format) {}
        
    };
    
    class BranchExecutionRuntime {
    
    private:
        
        io::BitReader branches;
        Output output;
    
    public:
        
        bool nextSingleBranch() noexcept {
            return branches.next();
        }
        
        u64 nextMultiBranch(u64 numBranches) noexcept {
            return branches.next(numBranches);
        }
        
        Func* nextInfiniteBranch() noexcept {
            const auto functionIndex = nextMultiBranch(__BranchExecution_numFunctions);
            return __BranchExecution_functionTable[functionIndex];
        }
        
        void onEdge(u64 startBlockIndex, u64 endBlockIndex) noexcept {
            output << Edge {.start = startBlockIndex, .end = endBlockIndex};
        }
        
        // TODO
        explicit BranchExecutionRuntime() noexcept(false)
                : branches(io::ReadOnlyMappedMemory<u64>("TODO")),
                  output(writer(coverage::output().dir, "branches.edges"), std::cout, true) {}
        
    };
    
    auto rt = LazilyConstructed<BranchExecutionRuntime>();
    
}

namespace {
    using runtime::coverage::branch::execute::rt;
    using runtime::coverage::branch::execute::Func;
}

#define api API_BranchExecution

bool api (nextSingleBranch)() noexcept {
    return rt().nextSingleBranch();
}

u64 api (nextMultiBranch)(u64 numBranches) noexcept {
    return rt().nextMultiBranch(numBranches);
}

Func* api(nextInfiniteBranch)() noexcept {
    return rt().nextInfiniteBranch();
}

void api (onEdge)(u64 startBlockIndex, u64 endBlockIndex) noexcept {
    //    printf("BranchExecution: onEdge: %lu, %lu\n", startBlockIndex, endBlockIndex);
    rt().onEdge(startBlockIndex, endBlockIndex);
}
