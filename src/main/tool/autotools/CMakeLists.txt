llvmImportAsLibrary()

add_compile_definitions(BUILD_PATH=\"${CMAKE_BINARY_DIR}\")
add_compile_definitions(BIN_PATH_FUZZ_AUTOTOOLS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")

set(files.share
        ../../../share/io/env/Environment.cpp
        ../../../share/io/env/Exec.cpp
        ../../../share/io/Popen.cpp
        ../../../share/io/fse.cpp
        ../../../share/concurrent/numVirtualCores.cpp
        )

add_link_options(-lstdc++fs)
llvmLinkLibrary()

set(target tool.fuzz.autotools)
add_executable(${target} fuzz.autotools.cpp ${files.share})
copyExecutable(${target})
aliasBin(${target} bin fuzz.autotools)
