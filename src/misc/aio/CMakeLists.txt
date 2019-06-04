llvmImportAsLibrary()

add_link_options(-lstdc++fs -lrt -pthread -ltinfo)
add_link_options("-L${llvm.lib.dir}" -lLLVMSupport)

add_executable(misc.aio aio.cpp ${files.share.aio} ${files.share.io})
