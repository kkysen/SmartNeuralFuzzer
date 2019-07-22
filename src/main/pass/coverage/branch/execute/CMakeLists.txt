addCoverageRuntimePathDefinition(branch.execute)

add_library(pass.coverage.branch.execute SHARED ${files.share} BranchExecutionPass.cpp)
copyLibrary(pass.coverage.branch.execute)
