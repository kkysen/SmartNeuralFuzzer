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
        ${files.share.llvm}
        ${files.pass.coverage}
        )

function(addCoverageRuntimePathDefinition name)
    add_compile_definitions(BIN_PATH_RUNTIME_COVERAGE=\"${CMAKE_BINARY_DIR}/lib/$<TARGET_FILE_NAME:runtime.coverage.${name}>\")
endfunction()

function(addCoveragePass name)
    set(pass coverage.${name})
    set(target pass.${pass})
    addCoverageRuntimePathDefinition(${name})
    add_compile_definitions(PASS_NAME=\"${target}\")
    add_library(${target} SHARED ${ARGN} ${files.share})
    copyLibrary(${target})
endfunction()

add_subdirectory(block)
add_subdirectory(branch)
add_subdirectory(edge)

add_custom_target(pass.coverage DEPENDS
        pass.coverage.block
        pass.coverage.edge
        pass.coverage.branch
        pass.coverage.branch.execute
        pass.coverage.branch.execute2
        )
