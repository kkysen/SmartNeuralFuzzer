add_subdirectory(pass)
add_subdirectory(runtime)
#add_subdirectory(tools)

add_custom_target(main DEPENDS pass runtime)
#add_custom_target(main DEPENDS pass runtime klang)
