add_library(pass.register SHARED register.cpp)
copyLibrary(pass.register)

add_subdirectory(preload)
