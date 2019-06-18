llvmImportAsLibrary()

files(runtime.coverage
        CoverageOutput.h
        CoverageOutput.cpp
        include.h
        BlockCoverageRuntime.h
        BlockCoverageRuntime.cpp
        BranchCoverageRuntime.h
        BranchCoverageRuntime.cpp
        )

set(files
        ${files.share.common}
        ${files.share.time}
        ${files.share.io}
        ${files.share.io.env}
        ${files.share.aio.signal}
        ${files.share.concurrent}
        ${files.share.hook}
        ${files.share.capability}
        ${files.runtime}
        ${files.runtime.coverage}
        )

set(target runtime.coverage)
add_library(${target} STATIC ${files})
copyLibraryBC(${target})
add_dependencies(${target} tool.ar.override.run)

