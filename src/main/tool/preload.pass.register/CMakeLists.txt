set(target tool.preload.pass.register)
add_executable(${target} preloadPassRegister.cpp ../../../share/io/LdPreload.cpp)
copyExecutable(${target})

function(copyAs alias)
    set(binDir bin)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy
            "$<TARGET_FILE:${target}>"
            "${CMAKE_BINARY_DIR}/${binDir}/${alias}"
            COMMENT "Copying $<TARGET_FILE_NAME:${target}> to ${CMAKE_BINARY_DIR} as ${alias}"
            )
endfunction()

copyAs(clang-${llvmVersionMajorNewest})
copyAs(opt-${llvmVersionMajorNewest})
