set(binDirs bin lib)
foreach (binDir ${binDirs})
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${binDir}")
endforeach ()
file(CREATE_LINK "${CMAKE_BINARY_DIR}/bin" "${CMAKE_SOURCE_DIR}/bin" SYMBOLIC)

add_compile_definitions(BIN_PATH=\"${CMAKE_BINARY_DIR}\")
add_compile_definitions(BIN_PATH_PASS_REGISTER=\"${CMAKE_BINARY_DIR}/lib/$<TARGET_FILE_NAME:pass.register>\")

add_subdirectory(pass)
add_subdirectory(runtime)
add_subdirectory(tool)

add_custom_target(main DEPENDS pass runtime tool)
