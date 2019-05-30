llvmImportAsLibrary()

llvmConfig(libdir llvm.lib.dir)

set(files.share ${files.share.aio} ${files.share.io})

add_link_options(-lrt -lpthread -ltinfo)
add_link_options("-L${llvm.lib.dir}" -lLLVMSupport)

add_executable(aio aio.cpp ${files.share})
