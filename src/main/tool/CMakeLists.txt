add_compile_definitions(BUILD_PATH=\"${CMAKE_BINARY_DIR}\")

add_subdirectory(opt)
add_subdirectory(preload.pass.register)
add_subdirectory(ar)
add_subdirectory(autotools)
add_subdirectory(parse)

add_custom_target(tool DEPENDS
        tool.opt
        tool.preload.pass.register
        tool.ar
        tool.ar.override
        tool.fuzz.autotools
        tool.fuzz.gnu.utils
        tool.parse
        )
