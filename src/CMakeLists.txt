add_compile_options(-fcolor-diagnostics)

set(CXX_LIBS /mnt/c/Users/Khyber/workspace/C++)

include(cmake/files.cmake)
include(cmake/Xclang.cmake)
include(cmake/llvmVersion.cmake)
include(cmake/llvmImport.cmake)

files(share.common
        share/common/numbers.h
        share/common/debug.h
        share/common/debug.cpp
        share/common/math.h
        share/common/lazy.h
        share/common/api.h
        )

files(share.io
        share/io/EnvironmentOutputPath.h
        share/io/EnvironmentOutputPath.cpp
        share/io/fs.h
        share/io/fse.h
        share/io/fse.cpp
        share/io/Write.h
        share/io/Write.cpp
        share/io/Buffer.h
        )

files(share.aio
        share/aio/ControlBlock.h
        share/aio/ControlBlock.cpp
        share/aio/WriteBufferPool.h
        share/aio/WriteBufferPool.cpp
        )

files(share.llvm
        share/llvm/Types.h
        share/llvm/Constants.h
        share/llvm/alignment.h
        share/llvm/IRBuilderExt.h
        share/llvm/AllocaArgs.h
        share/llvm/LoadStore.h
        share/llvm/LLVMArray.h
        share/llvm/debug.h
        share/llvm/debug.cpp
        share/llvm/api.h
        share/llvm/utils.h
        share/llvm/utils.cpp
        )

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

add_link_options("-fuse-ld=lld")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_compile_options(-Wall -Werror -Wextra -Wno-error=unused-parameter)

add_subdirectory(main)
add_subdirectory(test)
