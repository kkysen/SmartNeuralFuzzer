files(runtime.coverage.branch
        BranchCoverageRuntime.h
        BranchCoverageRuntime.cpp)

files(runtime.coverage.block
        BlockCoverageRuntime.h
        BlockCoverageRuntime.cpp)

add_library(runtime.coverage.branch STATIC ${files.share} ${files.runtime.coverage.branch})
add_library(runtime.coverage.block STATIC ${files.share} ${files.runtime.coverage.block})
