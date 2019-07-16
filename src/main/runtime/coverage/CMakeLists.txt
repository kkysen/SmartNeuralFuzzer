llvmImportAsLibrary()

files(runtime.coverage
        CoverageOutput.h
        CoverageOutput.cpp
        include.h
        BlockCoverageRuntime.h
        BlockCoverageRuntime.cpp
        EdgeCoverageRuntime.h
        EdgeCoverageRuntime.cpp
        BranchCoverageRuntime.h
        BranchCoverageRuntime.cpp
        BranchExecutionRuntime.h
        BranchExecutionRuntime.cpp
        )

set(files.all.runtime.coverage
        ${files.share.common}
        ${files.share.time}
        ${files.share.io}
        ${files.share.io.env}
        ${files.share.aio.signal}
        ${files.share.concurrent}
        ${files.share.hook}
        ${files.share.dl}
        ${files.share.capability}
        ${files.runtime}
        ${files.runtime.coverage}
        )

function(addRuntime target)
    add_library(${target} STATIC ${files.all.${target}})
    copyLibraryBC(${target})
    add_dependencies(${target} tool.ar.override.run)
endfunction()

addRuntime(runtime.coverage)
