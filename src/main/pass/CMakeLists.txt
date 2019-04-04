include(../../cmake/llvmVersion.cmake)

llvmImportAsRuntime()

set(files.share ${files.share.common} ${files.share.llvm})

add_library(pass.coverage.branch SHARED ${files.share} BranchCoveragePass.cpp)
add_library(pass.coverage.block SHARED ${files.share} BlockCoveragePass.cpp)
