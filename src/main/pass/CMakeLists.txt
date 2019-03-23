include(../../cmake/LLVMVersion.cmake)

if (${llvmVersionMajorIsNewest})
    llvmConfig(includedir llvmIncludes)
    include_directories("${llvmIncludes}")
    llvmConfig(prefix llvmPrefix)
    include_directories("${llvmPrefix}/include")
    
    llvmConfig(cxxflags llvmFlags)
    string(REGEX REPLACE "-std=[^ ]*" "" llvmFlags "${llvmFlags}")
else ()
    include_directories("${CXX_LIBS}/llvm-project/llvm/include/")
    include_directories("${CXX_LIBS}/llvm-project/build/clang/fewTargets/Release/include/")
    
    set(llvmMacros "-D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS")
    set(llvmExceptions "-fno-exceptions -fno-rtti")
    set(llvmFlags "${llvmExceptions} ${llvmMacros}")
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${llvmFlags}")

set(files.share ${files.share.common} ${files.share.llvm})

add_library(pass.coverage.branch SHARED ${files.share} BranchCoveragePass.cpp)
add_library(pass.coverage.block SHARED ${files.share} BlockCoveragePass.cpp)
