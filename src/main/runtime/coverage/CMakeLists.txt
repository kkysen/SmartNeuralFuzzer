llvmImportAsLibrary()

files(runtime.coverage
        CoverageOutput.h
        CoverageOutput.cpp
        )

set(files.share
        ${files.share.common}
        ${files.share.io}
        ${files.share.aio}
        ${files.runtime}
        ${files.runtime.coverage}
        )

add_subdirectory(branch)
add_subdirectory(block)

add_custom_target(runtime.coverage DEPENDS runtime.coverage.branch runtime.coverage.block)
