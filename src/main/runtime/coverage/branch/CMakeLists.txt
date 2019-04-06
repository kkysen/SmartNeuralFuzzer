files(runtime.coverage.branch
        BranchCoverageRuntime.h
        BranchCoverageRuntime.cpp)

add_library(runtime.coverage.branch STATIC ${files.share} ${files.runtime.coverage.branch})

target_link_libraries(runtime.coverage.branch stdc++fs)
