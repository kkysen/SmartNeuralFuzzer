add_library(pass.coverage.block SHARED BlockCoveragePass.cpp ${files.share} ../../../../share/io/env/Argv.cpp)
copyLibrary(pass.coverage.block)
