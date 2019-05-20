#add_link_options(-lstdc++)
add_link_options(-lstdc++fs)

files(runtime
        RuntimeOutput.h
        RuntimeOutput.cpp)

add_subdirectory(coverage)

add_custom_target(runtime)
add_dependencies(runtime runtime.coverage)
