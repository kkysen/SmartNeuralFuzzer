llvmImportAsLibrary()

set(files.share ${files.share.hooks} ${files.share.aio.signal})

add_link_options(-pthread -ldl)
add_link_options("-L${llvm.lib.dir}" -lLLVMSupport -ltinfo)

add_executable(share.hooks.libc.test test.cpp ${files.share})
