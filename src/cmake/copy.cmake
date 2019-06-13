function(copyFileToAs target binDir fileDir fileName alias)
    if ($<STREQUAL:${fileName},${alias}>)
        set(asAlias " as ${alias}")
    endif ()
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E create_symlink
            "${fileDir}/${fileName}"
            "${CMAKE_BINARY_DIR}/${binDir}/${alias}"
            COMMENT "Copying ${fileName} to ${CMAKE_BINARY_DIR}/${binDir}${asAlias}"
            )
endfunction()

function(aliasBin target binDir alias)
    copyFileToAs(${target} ${binDir} "${CMAKE_BINARY_DIR}/${binDir}" "$<TARGET_FILE_NAME:${target}>" ${alias})
endfunction()

function(copyFileTo target binDir fileName)
    copyFileToAs(${target} ${binDir} "$<TARGET_FILE_DIR:${target}>" ${fileName} ${fileName})
endfunction()

function(copyTargetTo target binDir)
    copyFileTo(${target} ${binDir} "$<TARGET_FILE_NAME:${target}>")
endfunction()

function(copyLibrary target)
    copyTargetTo(${target} lib)
endfunction()

function(copyExecutable target)
    copyTargetTo(${target} bin)
endfunction()

function(copyLibraryBC target)
    copyLibrary(${target})
    copyFileTo(${target} lib "lib${target}.bc")
endfunction()
