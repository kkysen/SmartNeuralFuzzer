set(files.share)

if (${llvmVersionMajorIsNewest})
    
    set(newestClang clang-${llvmVersionMajorNewest})
    set(CMAKE_C_COMPILER ${newestClang})
    set(CMAKE_CXX_COMPILER ${newestClang})
    set(newestClang)
    
    llvmPreloadPassRegister()
    
#    add_compile_options(-ftime-report)
    
    XclangLoadTargets(pass.coverage.block pass.coverage.branch)

endif ()

add_compile_options(-g)

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
set(tests.touch)
foreach (test ${tests})
    add_executable(${test} ${files.share} "${test}.cpp")
    target_link_libraries(${test} runtime.coverage.branch runtime.coverage.block)
    add_dependencies(${test} pass)
    
    add_custom_target(${test}.touch touch ${CMAKE_CURRENT_SOURCE_DIR}/${test}.cpp)
    list(APPEND tests.touch ${test}.touch)
endforeach ()

add_custom_target(test DEPENDS ${tests})
add_custom_target(test.touch DEPENDS ${tests.touch})
