set(files.share)

if (${llvmVersionMajorIsNewest})
    
    # this is the LD_PRELOAD wrapper executable
    set(newestClang ${CMAKE_BINARY_DIR}/bin/clang-9)
    set(CMAKE_C_COMPILER ${newestClang})
    set(CMAKE_CXX_COMPILER ${newestClang})
    set(newestClang)
    
    #    add_compile_options(-ftime-report)
    
    XclangLoadTargets(pass.coverage.block)
    #    XclangLoadTargets(pass.coverage.block pass.coverage.branch)

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
set(tests.bin)
foreach (test ${tests})
    add_executable(test.${test} ${files.share} "${test}.cpp")
    target_link_libraries(test.${test} runtime.coverage.branch runtime.coverage.block)
    add_dependencies(test.${test} pass)
    
    add_custom_target(test.${test}.touch touch ${CMAKE_CURRENT_SOURCE_DIR}/${test}.cpp)
    
    list(APPEND tests.bin test.${test})
    list(APPEND tests.touch test.${test}.touch)
endforeach ()

add_custom_target(test DEPENDS ${tests.bin})
add_custom_target(test.touch DEPENDS ${tests.touch})
