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
        ${files.share.io.env}
        ${files.share.aio.signal}
        ${files.share.concurrent}
        ${files.share.hook}
        ${files.share.dl}
        ${files.share.capability}
        ${files.runtime}
        ${files.runtime.coverage}
        )

function(addCoverageRuntime name)
    set(name coverage.${name})
    set(target runtime.${name})
    set(files.all.${target}
            ${files.share}
            ${files.${target}}
            )
    addRuntime(${name})
endfunction()

add_subdirectory(block)
add_subdirectory(edge)
add_subdirectory(branch)

add_custom_target(runtime.coverage DEPENDS
        runtime.coverage.block
        runtime.coverage.edge
        runtime.coverage.branch
        runtime.coverage.branch.execute
        )
