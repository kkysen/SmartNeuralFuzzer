
add_library(pass.register SHARED
        register.cpp
        ../../../share/io/env/LdPreload.cpp
        ../../../share/hook/libc/syscall/getpid.cpp
        ../../../share/hook/libc/syscall/gettid.cpp
        )
copyLibrary(pass.register)
