#add_link_options(-lstdc++)
add_link_options(-lstdc++fs)

files(runtime
        RuntimeOutput.h
        RuntimeOutput.cpp)

function(addRuntime name)
    set(target runtime.${name})
    add_library(${target} STATIC ${files.all.${target}})
    copyLibraryBC(${target})
    add_dependencies(${target} tool.ar.override.run)
endfunction()

add_subdirectory(coverage)

add_custom_target(runtime DEPENDS
        runtime.coverage
        )
