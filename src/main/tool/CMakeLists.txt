add_subdirectory(preload.pass.register)
add_subdirectory(ar)
add_subdirectory(autotools)
add_subdirectory(parse)

add_custom_target(tool DEPENDS
        tool.preload.pass.register
        tool.ar
        tool.ar.override
        tool.fuzz.autotools
        tool.fuzz.gnu.utils
        tool.parse
        )
