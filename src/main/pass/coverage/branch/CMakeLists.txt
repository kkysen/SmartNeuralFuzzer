files(pass.coverage.branch
        SwitchCaseSuccessors.h
        SwitchCaseSuccessors.cpp
        )

set(files.share ${files.pass.coverage.branch} ${files.share})

add_library(pass.coverage.branch SHARED ${files.share} BranchCoveragePass.cpp)
copyLibrary(pass.coverage.branch)

add_library(pass.coverage.branch.execute SHARED ${files.share} BranchExecutionPass.cpp)
copyLibrary(pass.coverage.branch.execute)
