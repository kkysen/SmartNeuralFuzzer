llvmImportAsLibrary()

set(target tool.ar)
add_executable(${target} ar.cpp)
copyExecutable(${target})

set(bin.path.ar.lock "${CMAKE_BINARY_DIR}/ar.lock")
add_compile_definitions(BIN_PATH_AR=\"${CMAKE_BINARY_DIR}/bin/$<TARGET_FILE_NAME:tool.ar>\")
add_compile_definitions(BIN_PATH_AR_LOCK=\"${bin.path.ar.lock}\")

# remove to notify override that stuff has changed again
file(REMOVE ${bin.path.ar.lock})

add_link_options(-lstdc++fs)

set(target tool.ar.override)
add_executable(${target} override.cpp ${files.share}
        ../../../share/io/Popen.cpp ../../../share/io/fse.cpp)
copyExecutable(${target})

add_custom_target(tool.ar.override.run ALL $<TARGET_FILE:${target}>
        DEPENDS tool.ar
        )
