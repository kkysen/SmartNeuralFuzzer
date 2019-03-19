add_compile_options(-fcolor-diagnostics)

set(CXX_LIBS /mnt/c/Users/Khyber/workspace/C++)

include(cmake/files.cmake)

files(share.common
        share/common/numbers.h
        share/common/debug.h
        share/common/math.h
        share/common/fs.h
        share/common/fse.h)

files(share.llvm
        share/llvm/Types.h
        share/llvm/Constants.h
        share/llvm/alignment.h
        share/llvm/IRBuilderExt.h
        share/llvm/AllocaArgs.h
        share/llvm/LoadStore.h
        share/llvm/LLVMArray.h
        share/llvm/api.h
        share/llvm/debug.h)

set(files.share
        ${files.share.common}
        ${files.share.llvm}
        )

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

add_subdirectory(main)
add_subdirectory(test)
