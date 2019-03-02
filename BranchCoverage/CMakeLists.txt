cmake_minimum_required(VERSION 3.11)
project(BranchCoverage CXX)

set(CMAKE_CXX_STANDARD 17)

set(CXX_LIBS /mnt/c/Users/Khyber/workspace/C++)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

include_directories(.)
include_directories(${CXX_LIBS}/llvm-project/llvm/include/)
include_directories(${CXX_LIBS}/llvm-project/build/clang/fewTargets/Release/include/)

set(MACROS "-D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS")
set(EXCEPTIONS "-fno-exceptions -fno-rtti")
set(FLAGS "${EXCEPTIONS} ${MACROS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

set(SOURCE_FILES
        BranchCoveragePass.cpp
        BranchCoveragePass.h
        LLVMArray.h
        Types.h
        Constants.h
        IRBuilderExt.h
        LoadStore.h
        alignment.h
        AllocaArgs.h
        debug.h
        )

add_library(BranchCoverage SHARED ${SOURCE_FILES})

add_executable(run run.cpp)