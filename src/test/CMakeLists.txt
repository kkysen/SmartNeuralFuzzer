set(files.share ${files.share.common})

llvmPreloadPassRegister()

# TODO switch order?
XclangLoadTargets(pass.coverage.branch pass.coverage.block)

set(tests branch switch optimizedSwitch argcLoop nLoop virtualCall staticConstructors)
foreach (test ${tests})
    add_executable(${test} ${files.share} "${test}.cpp")
    target_link_libraries(${test} runtime.coverage.branch runtime.coverage.block)
    add_dependencies(${test} pass)
endforeach ()

add_custom_target(test)
add_dependencies(test ${tests})
