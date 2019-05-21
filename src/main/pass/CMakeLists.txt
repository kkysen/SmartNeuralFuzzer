llvmImportAsRuntime()

add_link_options(-lstdc++fs)

files(pass
        BinaryFunctionFilter.h
        BinaryFunctionFilter.cpp
        )

add_subdirectory(register)
add_subdirectory(coverage)
add_subdirectory(unitTest)

add_custom_target(pass)
add_dependencies(pass pass.register pass.coverage)
