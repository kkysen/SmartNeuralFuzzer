cmake_minimum_required(VERSION 3.11)
project(SmartNeuralFuzzer CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

include_directories(.)

set(CXX_LIBS /mnt/c/Users/Khyber/workspace/C++)

include(src/cmake/LLVMVersion.cmake)

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

set(CommonShareFiles
        src/share/common/numbers.h
        src/share/common/debug.h
        src/share/common/math.h src/share/common/fs.h)

set(LLVMShareFiles
        src/share/llvm/Types.h
        src/share/llvm/Constants.h
        src/share/llvm/alignment.h
        src/share/llvm/IRBuilderExt.h
        src/share/llvm/AllocaArgs.h
        src/share/llvm/LoadStore.h
        src/share/llvm/LLVMArray.h
        src/share/llvm/api.h
        src/share/llvm/debug.h)

set(ShareFiles
        ${CommonShareFiles}
        ${LLVMShareFiles}
        )

set(BranchCoveragePassFiles
        src/main/BranchCoverage/pass/BranchCoveragePass.cpp
        )

set(BranchCoverageRuntimeFiles
        src/main/BranchCoverage/runtime/BranchCoverageRuntime.cpp
        src/main/BranchCoverage/runtime/BranchCoverageRuntime.h
        )

set(BlockCoveragePassFiles
        src/main/BlockCoverage/pass/BlockCoveragePass.cpp
        )

set(BlockCoverageRuntimeFiles
        src/main/BlockCoverage/runtime/BlockCoverageRuntime.cpp
        src/main/BlockCoverage/runtime/BlockCoverageRuntime.h
        )

add_library(BranchCoveragePass SHARED ${ShareFiles} ${BranchCoveragePassFiles})
add_library(BranchCoverageRuntime STATIC ${ShareFiles} ${BranchCoverageRuntimeFiles})
add_library(BlockCoveragePass SHARED ${ShareFiles} ${BlockCoveragePassFiles})
add_library(BlockCoverageRuntime STATIC ${ShareFiles} ${BlockCoverageRuntimeFiles})

add_executable(branch ${CommonShareFiles} src/test/branch.cpp)
add_executable(switch ${CommonShareFiles} src/test/switch.cpp)
add_executable(optimizedSwitch ${CommonShareFiles} src/test/optimizedSwitch.cpp)
add_executable(loop ${CommonShareFiles} src/test/loop.cpp)
add_executable(virtualCall ${CommonShareFiles} src/test/virtualCall.cpp)
