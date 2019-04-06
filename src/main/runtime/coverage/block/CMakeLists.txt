files(runtime.coverage.block
        BlockCoverageRuntime.h
        BlockCoverageRuntime.cpp)

add_library(runtime.coverage.block STATIC ${files.share} ${files.runtime.coverage.block})

target_link_libraries(runtime.coverage.block stdc++fs)
