add_subdirectory(pass)
add_subdirectory(runtime)

add_custom_target(main)
add_dependencies(main pass runtime)
