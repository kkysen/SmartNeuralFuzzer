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
        share/common/has/field.h
        share/common/has/method.h
        share/common/deleteCopy.h
        share/common/odrUse.h
        share/common/odrUse.cpp
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
        share/stde/ListDeleter.h
        share/stde/ListDeleter.cpp
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
        )

files(share.aio.signal
        share/aio/signal/Flag.h
        share/aio/signal/Flag.cpp
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
        share/aio/signal/mask/Init.h
        share/aio/signal/mask/Init.cpp
        share/aio/signal/mask/Modify.h
        share/aio/signal/mask/Modify.cpp
        share/aio/signal/mask/How.h
        share/aio/signal/mask/How.cpp
        share/aio/signal/mask/Apply.h
        share/aio/signal/mask/Apply.cpp
        share/aio/signal/mask/Mask.h
        share/aio/signal/mask/Mask.cpp
        share/aio/signal/mask/Masker.h
        share/aio/signal/mask/Masker.cpp
        )

files(share.concurrent
        share/concurrent/NoLock.h
        share/concurrent/NoLock.cpp
        share/concurrent/numVirtualCores.h
        share/concurrent/numVirtualCores.cpp
        share/concurrent/SpinLock.h
        share/concurrent/SpinLock.cpp
        share/concurrent/Mutex.cpp
        share/concurrent/Mutex.h
        share/concurrent/AdaptiveMutex.h
        share/concurrent/AdaptiveMutex.cpp
        )

set(share.hooks.libc.syscall
        share/hooks/libc/syscall/impl.h
        share/hooks/libc/syscall/impl.cpp
        share/hooks/libc/syscall/gettid.h
        share/hooks/libc/syscall/gettid.cpp
        share/hooks/libc/syscall/tgkill.h
        share/hooks/libc/syscall/tgkill.cpp
        )

files(share.hooks.libc.syscall
        ${share.hooks.libc.syscall}
        )

files(share.hooks
        ${share.hooks.libc.syscall}
        share/hooks/libc/impl.h
        share/hooks/libc/impl.cpp
        share/hooks/libc/hooks.cpp
        share/hooks/lifecycle/hooks.h
        share/hooks/lifecycle/hooks.cpp
        share/hooks/lifecycle/LifeCycle.h
        share/hooks/lifecycle/LifeCycle.cpp
        share/hooks/lifecycle/LifeCycles.h
        share/hooks/lifecycle/LifeCycles.cpp
        share/hooks/lifecycle/LazilyConstructed.h
        share/hooks/lifecycle/LazilyConstructed.cpp
        share/hooks/lifecycle/ThreadLifeCycles.h
        share/hooks/lifecycle/ThreadLifeCycles.cpp
        share/hooks/lifecycle/ThreadLifeCyclesOwner.h
        share/hooks/lifecycle/ThreadLifeCyclesOwner.cpp
        share/hooks/lifecycle/ProcessLifeCycles.h
        share/hooks/lifecycle/ProcessLifeCycles.cpp
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
add_subdirectory(misc)

add_subdirectory(share/hooks/libc/test)
