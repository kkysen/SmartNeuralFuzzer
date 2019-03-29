set(files.share ${files.share.common})

XclangLoadTargets(pass.coverage.branch pass.coverage.block)

add_executable(branch ${files.share} branch.cpp)
add_executable(switch ${files.share} switch.cpp)
add_executable(optimizedSwitch ${files.share} optimizedSwitch.cpp)
add_executable(loop ${files.share} loop.cpp)
add_executable(virtualCall ${files.share} virtualCall.cpp)
add_executable(staticConstructors ${files.share} staticConstructors.cpp)

target_link_libraries(branch runtime.coverage.branch runtime.coverage.block)
target_link_libraries(switch runtime.coverage.branch runtime.coverage.block)
target_link_libraries(optimizedSwitch runtime.coverage.branch runtime.coverage.block)
target_link_libraries(loop runtime.coverage.branch runtime.coverage.block)
target_link_libraries(virtualCall runtime.coverage.branch runtime.coverage.block)
target_link_libraries(staticConstructors runtime.coverage.branch runtime.coverage.block)

add_dependencies(branch pass.coverage.branch pass.coverage.block)
add_dependencies(switch pass.coverage.branch pass.coverage.block)
add_dependencies(optimizedSwitch pass.coverage.branch pass.coverage.block)
add_dependencies(loop pass.coverage.branch pass.coverage.block)
add_dependencies(virtualCall pass.coverage.branch pass.coverage.block)
add_dependencies(staticConstructors pass.coverage.branch pass.coverage.block)
