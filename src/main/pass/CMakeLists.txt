llvmImportAsRuntime()

add_subdirectory(register)
add_subdirectory(coverage)

add_custom_target(pass DEPENDS pass.register pass.register.preload pass.coverage)
