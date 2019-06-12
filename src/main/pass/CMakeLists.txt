llvmImportAsRuntime()

add_subdirectory(register)
add_subdirectory(coverage)

add_custom_target(pass DEPENDS pass.register pass.coverage)
