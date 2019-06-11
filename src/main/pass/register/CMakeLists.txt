files(share
        ../../../share/stde/split.h
        ../../../share/stde/split.cpp
        ../../../share/io/LdPreload.h
        ../../../share/io/LdPreload.cpp
        )

add_compile_definitions(BIN_PATH_PASS_REGISTER=\"${CMAKE_BINARY_DIR}/lib/$<TARGET_FILE_NAME:pass.register>\")

add_library(pass.register SHARED register.cpp ${files.share})
copyLibrary(pass.register)

add_subdirectory(preload)
