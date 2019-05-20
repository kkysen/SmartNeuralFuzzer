files(runtime.coverage.block
        BlockCoverageRuntime.h
        BlockCoverageRuntime.cpp)

add_library(runtime.coverage.block STATIC ${files.share} ${files.runtime.coverage.block})
