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
        share/aio/signal/handler/Const.h
        share/aio/signal/handler/Const.cpp
        share/aio/signal/handler/Flag.h
        share/aio/signal/handler/Flag.cpp
        share/aio/signal/Value.h
        share/aio/signal/Value.cpp
        share/aio/signal/Info.h
        share/aio/signal/Info.cpp
        share/aio/signal/Info_checkMemoryLayout.cpp
        share/aio/signal/Context.h
        share/aio/signal/Context.cpp
        share/aio/signal/Disposition.h
        share/aio/signal/Disposition.cpp
        share/aio/signal/Signal.h
        share/aio/signal/Signal.cpp
        share/aio/signal/handler/Raw.h
        share/aio/signal/handler/UnMaskedAction.h
        share/aio/signal/handler/UnMaskedAction.cpp
        share/aio/signal/handler/AltStack.h
        share/aio/signal/handler/AltStack.cpp
        share/aio/signal/handler/Func.h
        share/aio/signal/handler/Base.h
        share/aio/signal/handler/Base.cpp
        share/aio/signal/handler/Resilient.h
        share/aio/signal/handler/Resilient.cpp
        share/aio/signal/handler/Passive.h
        share/aio/signal/handler/Passive.cpp
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
        share/concurrent/numVirtualCores.h
        share/concurrent/numVirtualCores.cpp
        share/concurrent/lock/NoLock.h
        share/concurrent/lock/NoLock.cpp
        share/concurrent/lock/SpinLock.h
        share/concurrent/lock/SpinLock.cpp
        share/concurrent/lock/Mutex.cpp
        share/concurrent/lock/Mutex.h
        share/concurrent/lock/AdaptiveMutex.h
        share/concurrent/lock/AdaptiveMutex.cpp
        share/concurrent/ConditionVariable.h
        share/concurrent/ConditionVariable.cpp
        share/concurrent/container/ListDeleter.h
        share/concurrent/container/ListDeleter.cpp
        share/concurrent/container/ThreadList.h
        share/concurrent/container/ThreadList.cpp
        )

set(share.hook.libc.syscall
        share/hook/libc/syscall/impl.h
        share/hook/libc/syscall/impl.cpp
        share/hook/libc/syscall/gettid.h
        share/hook/libc/syscall/gettid.cpp
        share/hook/libc/syscall/tgkill.h
        share/hook/libc/syscall/tgkill.cpp
        share/hook/libc/syscall/sigqueueinfo.h
        share/hook/libc/syscall/sigqueueinfo.cpp
        share/hook/libc/syscall/cap.h
        share/hook/libc/syscall/cap.cpp
        )

files(share.hook.libc.syscall
        ${share.hook.libc.syscall}
        )

files(share.hook
        ${share.hook.libc.syscall}
        share/hook/libc/impl.h
        share/hook/libc/impl.cpp
        share/hook/libc/hooks.h
        share/hook/libc/hooks.cpp
        share/hook/libc/hooksImpl/include.h
        share/hook/libc/hooksImpl/fork.cpp
        share/hook/libc/hooksImpl/exec.cpp
        share/hook/libc/hooksImpl/execVariadic.cpp
        share/hook/libc/hooksImpl/exit.cpp
        share/hook/libc/hooksImpl/warnings.cpp
        share/hook/libc/hooksImpl/reboot.cpp
        share/hook/libc/hooksImpl/signals.h
        share/hook/libc/hooksImpl/signals.cpp
        share/hook/libc/hooksImpl/blocked.cpp
        share/hook/libc/hooksImpl/Wrapped.h
        share/hook/libc/hooksImpl/Wrapped.cpp
        share/hook/lifecycle/hooks.h
        share/hook/lifecycle/hooks.cpp
        share/hook/lifecycle/LifeCycle.h
        share/hook/lifecycle/LifeCycle.cpp
        share/hook/lifecycle/LifeCycles.h
        share/hook/lifecycle/LifeCycles.cpp
        share/hook/lifecycle/LazilyConstructed.h
        share/hook/lifecycle/LazilyConstructed.cpp
        share/hook/lifecycle/ThreadLifeCycles.h
        share/hook/lifecycle/ThreadLifeCycles.cpp
        share/hook/lifecycle/ProcessLifeCycles.h
        share/hook/lifecycle/ProcessLifeCycles.cpp
        share/hook/lifecycle/signaling/signaling.h
        share/hook/lifecycle/signaling/signaling.cpp
        share/hook/lifecycle/signaling/Sender.h
        share/hook/lifecycle/signaling/Sender.cpp
        share/hook/lifecycle/signaling/Receiver.h
        share/hook/lifecycle/signaling/Receiver.cpp
        )

files(share.capability
        share/capability/Capability.h
        share/capability/Capability.cpp
        share/capability/fields.h
        share/capability/Version.h
        share/capability/Version.cpp
        share/capability/Header.h
        share/capability/Header.cpp
        share/capability/DirectCapabilitySet.h
        share/capability/DirectCapabilitySet.cpp
        share/capability/Data.h
        share/capability/Data.cpp
        share/capability/Capabilities.h
        share/capability/Capabilities.cpp
        share/capability/reboot.h
        share/capability/reboot.cpp
        share/capability/BitCache.h
        share/capability/BitCache.cpp
        share/capability/BitCached.h
        share/capability/BitCached.cpp
        share/capability/prctl.h
        share/capability/prctl.cpp
        share/capability/Bound.h
        share/capability/Bound.cpp
        share/capability/Ambient.h
        share/capability/Ambient.cpp
        share/capability/IndirectCapabilitySet.h
        share/capability/IndirectCapabilitySet.cpp
        share/capability/BoundSet.h
        share/capability/BoundSet.cpp
        share/capability/AmbientSet.h
        share/capability/AmbientSet.cpp
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

#set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

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

add_subdirectory(share/hook/libc/test)
