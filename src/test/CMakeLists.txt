set(files.share)

if (${llvmVersionMajorIsNewest})
    
    set(newestClang clang-${llvmVersionMajorNewest})
    set(CMAKE_C_COMPILER ${newestClang})
    set(CMAKE_CXX_COMPILER ${newestClang})
    set(newestClang)
    
    llvmPreloadPassRegister()
    
    XclangLoadTargets(pass.coverage.block pass.coverage.branch)

endif ()

# not sure why these are needed, they weren't before
add_link_options(-lstdc++)
add_link_options(-lstdc++fs)

set(tests
        branch
        switch
        optimizedSwitch
        argcLoop
        nLoop
        virtualCall
        staticConstructors
        using_libstdc++
        )
foreach (test ${tests})
    add_executable(${test} ${files.share} "${test}.cpp")
    target_link_libraries(${test} runtime.coverage.branch runtime.coverage.block)
    add_dependencies(${test} pass)
endforeach ()

add_custom_target(test)
add_dependencies(test ${tests})
