files(runtime.coverage.branch
        BranchCoverageRuntime.h
        BranchCoverageRuntime.cpp
        BranchCoverageRuntime.cpp)

files(runtime.coverage.block
        BlockCoverageRuntime.h
        BlockCoverageRuntime.cpp)

set(files.share ${files.share.common} ${files.share.io})

add_library(runtime.coverage.branch STATIC ${files.share} ${files.runtime.coverage.branch})
add_library(runtime.coverage.block STATIC ${files.share} ${files.runtime.coverage.block})

target_link_libraries(runtime.coverage.branch lstdc++fs)
target_link_libraries(runtime.coverage.block lstdc++fs)
