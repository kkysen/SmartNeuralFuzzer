set(files.share ${files.share.common})

add_executable(branch ${files.share} branch.cpp)
add_executable(switch ${files.share} switch.cpp)
add_executable(optimizedSwitch ${files.share} optimizedSwitch.cpp)
add_executable(loop ${files.share} loop.cpp)
add_executable(virtualCall ${files.share} virtualCall.cpp)
add_executable(staticConstructors ${files.share} staticConstructors.cpp)
