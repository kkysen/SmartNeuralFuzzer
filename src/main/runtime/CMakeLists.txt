add_subdirectory(coverage)

add_custom_target(runtime)
add_dependencies(runtime runtime.coverage)
