llvmImportAsLibrary()

files(runtime.coverage
        CoverageOutput.h
        CoverageOutput.cpp
        include.h
        )

set(files.share
        ${files.share.common}
        ${files.share.time}
        ${files.share.io}
        ${files.share.aio}
        ${files.share.aio.signal}
        ${files.share.concurrent}
        ${files.share.hooks}
        ${files.runtime}
        ${files.runtime.coverage}
        )

add_subdirectory(branch)
add_subdirectory(block)

add_custom_target(runtime.coverage DEPENDS runtime.coverage.branch runtime.coverage.block)
