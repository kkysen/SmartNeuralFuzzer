add_link_options(-lstdc++fs)

add_link_options(-L${llvm.lib.dir} -lLLVMSupport)
add_link_options(-L${llvm.lib.dir} -lLLVMCore)

add_link_options(-pthread)
add_link_options(-ltinfo)

add_executable(pass.coverage.test
        testBinaryFunctionFilter.cpp
        ${files.share.common}
        ${files.share.common.debug}
        ${files.share.stde}
        ${files.share.time}
        ${files.share.io}
        ${files.share.llvm.lib}
        ${files.pass.coverage}
        ../../../../share/hook/libc/syscall/getpid.cpp
        ../../../../share/hook/libc/syscall/gettid.cpp
        )
