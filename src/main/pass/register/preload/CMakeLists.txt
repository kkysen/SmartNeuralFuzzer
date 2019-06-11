
add_executable(pass.register.preload preloadPassRegister.cpp ${files.share} ${files.share.common})
copyExecutable(pass.register.preload)

function(copyAs alias)
    set(target pass.register.preload)
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
