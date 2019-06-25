set(files.share
        ${files.share.io}
        )

add_link_options(-lstdc++fs)

set(target tool.parse.blocks)
add_executable(${target} parse.cpp ${files.share})
copyExecutable(${target})
aliasBin(${target} bin parse.blocks)

add_custom_target(tool.parse DEPENDS
        tool.parse.blocks
        )
