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

files(share.stde
        share/stde/contains.h
        share/stde/contains.cpp
        share/stde/c_str.h
        share/stde/c_str.cpp
        share/stde/getline.h
        share/stde/getline.cpp
        share/stde/reversed.h
        share/stde/reversed.cpp
        )

files(share.time
        share/time/TimeSpec.h
        share/time/TimeSpec.cpp
        share/time/Clock.h
        share/time/Clock.cpp
        )

files(share.io
        share/io/EnvironmentOutputPath.h
        share/io/EnvironmentOutputPath.cpp
        share/io/fs.h
        share/io/fse.h
        share/io/fse.cpp
        share/io/Stat.h
        share/io/Stat.cpp
        share/io/Dir.h
        share/io/Dir.cpp
        share/io/Writer.h
        share/io/Writer.cpp
        share/io/WriteBuffer.h
        share/io/ReadOnlyMappedMemory.h
        share/io/ReadOnlyMappedMemory.cpp
        share/io/Popen.h
        share/io/Popen.cpp
        )

files(share.aio
        share/aio/ControlBlock.h
        share/aio/ControlBlock.cpp
        share/aio/IdempotentWriter.h
        share/aio/IdempotentWriter.cpp
        share/aio/WriteBufferPool.h
        share/aio/WriteBufferPool.cpp
        share/aio/WriteBufferBase.h
        share/aio/WriteBufferBase.cpp
        share/aio/StandardWriteBuffer.h
        share/aio/StandardWriteBuffer.cpp
        share/aio/BoolWriteBuffer.h
        share/aio/BoolWriteBuffer.cpp
        share/aio/signal/Info.h
        share/aio/signal/Info.cpp
        share/aio/signal/Info_checkMemoryLayout.cpp
        share/aio/signal/Context.h
        share/aio/signal/Context.cpp
        share/aio/signal/Disposition.h
        share/aio/signal/Disposition.cpp
        share/aio/signal/Signal.h
        share/aio/signal/Signal.cpp
        share/aio/signal/RawHandler.h
        share/aio/signal/UnMaskedAction.h
        share/aio/signal/UnMaskedAction.cpp
        share/aio/signal/AltStack.h
        share/aio/signal/AltStack.cpp
        share/aio/signal/Handler.h
        share/aio/signal/Handler.cpp
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
        share/llvm/registerStandardPass.h
        share/llvm/conversions.h
        share/llvm/conversions.cpp
        share/llvm/BinaryFunctionFilter.h
        share/llvm/BinaryFunctionFilter.cpp
        )

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

add_link_options("-fuse-ld=lld")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_compile_options(-Wall -Werror -Wextra -Wno-error=unused-parameter)

function(copyTargetTo target binDir)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy
            "$<TARGET_FILE:${target}>"
            "${CMAKE_BINARY_DIR}/${binDir}/$<TARGET_FILE_NAME:${target}>"
            COMMENT "Copying $<TARGET_FILE_NAME:${target}> to ${CMAKE_BINARY_DIR}"
            )
endfunction()

function(copyLibrary target)
    copyTargetTo(${target} lib)
endfunction()

function(copyExecutable target)
    copyTargetTo(${target} bin)
endfunction()

add_subdirectory(main)
add_subdirectory(test)
