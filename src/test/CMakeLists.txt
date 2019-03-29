set(files.share ${files.share.common})

XclangLoadTargets(pass.coverage.branch pass.coverage.block)

set(tests branch switch optimizedSwitch loop virtualCall staticConstructors)
foreach (test ${tests})
    add_executable(${test} ${files.share} "${test}.cpp")
    target_link_libraries(${test} runtime.coverage.branch runtime.coverage.block)
    add_dependencies(${test} pass.coverage.branch pass.coverage.block)
endforeach ()
