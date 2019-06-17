llvmImportAsLibrary()

set(libraries -lstdc++fs -ldl ${llvm.link.libs})
string(REPLACE ";" " " libraries "${libraries}")

add_compile_definitions(BUILD_PATH=\"${CMAKE_BINARY_DIR}\")
add_compile_definitions(BIN_PATH_FUZZ_AUTOTOOLS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")
add_compile_definitions(RUNTIME_COVERAGE_LIBRARIES=\"${libraries}\")

set(target tool.fuzz.autotools)
add_executable(${target} fuzz.autotools.cpp)
copyExecutable(${target})
aliasBin(${target} bin fuzz.autotools)
