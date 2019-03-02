cmake_minimum_required(VERSION 3.9)
project(DifferentiableFuzzer CXX)

set(CMAKE_CXX_STANDARD 17)

set(CXX_LIBS /mnt/c/Users/Khyber/workspace/C++)

include_directories(.)
include_directories(${CXX_LIBS}/llvm-project/llvm/include/)
include_directories(${CXX_LIBS}/llvm-project/compiler-rt/include/)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(COVERAGE_FLAGS "-fsanitize-coverage=trace-pc-guard,trace-cmp")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COVERAGE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_FLAGS}")

#set(CMAKE_C_OPTIMIZATION_FLAGS "-O0 -flto")
#set(CMAKE_C_ERROR_FLAGS "-Wall -Werror -Wextra")
#set(CMAKE_C_NO_ERROR_FLAGS "-Wno-error=unused-function -Wno-error=unused-parameter")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_ERROR_FLAGS} ${CMAKE_C_NO_ERROR_FLAGS} ${CMAKE_C_OPTIMIZATION_FLAGS}")

set(HOOKS_FILES
        hooks/main.cpp
        hooks/main.h
        hooks/hooks.cpp
        hooks/hooks.h
        hooks/Tracer.cpp
        hooks/Tracer.h
        )

set(TRANSFORM_FILES
        BranchCoverage/BranchCoveragePass.cpp
        BranchCoverage/BranchCoveragePass.h
        BranchCoverage/LLVMArray.cpp
        BranchCoverage/LLVMArray.h
        BranchCoverage/Types.cpp
        BranchCoverage/Types.h
        BranchCoverage/Constants.cpp
        BranchCoverage/Constants.h
        )

add_executable(DifferentiableFuzzer ${HOOKS_FILES})

add_library(BranchCoverage SHARED ${TRANSFORM_FILES})

