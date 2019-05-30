llvmImportAsLibrary()

llvmConfig(libdir llvm.lib.dir)

set(files.share ${files.share.hooks} ${files.share.aio.signal})

add_link_options(-lpthread -ldl)
add_link_options("-L${llvm.lib.dir}" -lLLVMSupport -ltinfo)

add_executable(share.hooks.libc.test test.cpp ${files.share})
