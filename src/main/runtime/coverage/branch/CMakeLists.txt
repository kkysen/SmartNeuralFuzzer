files(runtime.coverage.branch
        BranchCoverageRuntime.h
        BranchCoverageRuntime.cpp)

add_library(runtime.coverage.branch STATIC ${files.share} ${files.runtime.coverage.branch})
