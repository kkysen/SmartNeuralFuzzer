llvmImportAsRuntime()

add_link_options(-lstdc++fs)

files(pass.coverage
        includes.h
        runtimeFunctionFilter.h
        runtimeFunctionFilter.cpp
        )

set(files.share
        ${files.share.common}
        ${files.share.common.debug}
        ${files.share.stde}
        ${files.share.time}
        ${files.share.io}
        ${files.share.hook.libc.syscall}
        ${files.share.llvm}
        ${files.pass.coverage}
        )

add_compile_definitions(BIN_PATH_RUNTIME_COVERAGE_BLOCK=\"${CMAKE_BINARY_DIR}/lib/$<TARGET_FILE_NAME:runtime.coverage.block>\")
add_compile_definitions(BIN_PATH_RUNTIME_COVERAGE_BRANCH=\"${CMAKE_BINARY_DIR}/lib/$<TARGET_FILE_NAME:runtime.coverage.branch>\")

add_subdirectory(block)
add_subdirectory(branch)

add_custom_target(pass.coverage DEPENDS pass.coverage.block pass.coverage.branch)
