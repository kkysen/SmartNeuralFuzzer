llvmImportAsRuntime()

add_link_options(-lstdc++fs)

add_subdirectory(register)
add_subdirectory(coverage)

add_custom_target(pass)
add_dependencies(pass pass.register pass.coverage)
