add_subdirectory(preload.pass.register)
add_subdirectory(ar)

add_custom_target(tool DEPENDS tool.preload.pass.register tool.ar tool.ar.override)
