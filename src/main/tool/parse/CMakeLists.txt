
set(target tool.parse.blocks)
add_executable(${target} parse.cpp)
copyExecutable(${target})
aliasBin(${target} bin parse.blocks)
