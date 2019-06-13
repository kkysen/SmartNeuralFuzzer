add_compile_definitions(BUILD_PATH=\"${CMAKE_BINARY_DIR}\")
add_compile_definitions(BIN_PATH_FUZZ_AUTOTOOLS_SH=\"${CMAKE_CURRENT_SOURCE_DIR}\")

set(target tool.fuzz.autotools)
add_executable(${target} fuzz.autotools.cpp)
copyExecutable(${target})
aliasBin(${target} bin fuzz.autotools)
