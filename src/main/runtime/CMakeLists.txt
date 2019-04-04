llvmImportAsLibrary()

files(runtime.coverage.branch
        BranchCoverageRuntime.h
        BranchCoverageRuntime.cpp)

files(runtime.coverage.block
        BlockCoverageRuntime.h
        BlockCoverageRuntime.cpp)

set(files.share ${files.share.common} ${files.share.io} ${files.share.aio})

add_library(runtime.coverage.branch STATIC ${files.share} ${files.runtime.coverage.branch})
add_library(runtime.coverage.block STATIC ${files.share} ${files.runtime.coverage.block})

target_link_libraries(runtime.coverage.branch stdc++fs)
target_link_libraries(runtime.coverage.block stdc++fs)
