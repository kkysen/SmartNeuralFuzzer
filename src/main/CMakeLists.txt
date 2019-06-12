
add_compile_definitions(BIN_PATH=\"${CMAKE_BINARY_DIR}\")
add_compile_definitions(BIN_PATH_PASS_REGISTER=\"${CMAKE_BINARY_DIR}/lib/$<TARGET_FILE_NAME:pass.register>\")

add_subdirectory(pass)
add_subdirectory(runtime)
add_subdirectory(tool)

add_custom_target(main DEPENDS pass runtime tool)
