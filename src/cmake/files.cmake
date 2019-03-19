function(files var)
    list(TRANSFORM
            ARGN
            PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/"
            OUTPUT_VARIABLE outputFiles)
    set("files.${var}" ${outputFiles} PARENT_SCOPE)
endfunction()

function(includeRelative file)
    include("${CMAKE_CURRENT_SOURCE_DIR}/${file}")
endfunction()
