
set(target tool.parse)
add_executable(${target} parse.cpp)
copyExecutable(${target})
aliasBin(${target} bin parse)
