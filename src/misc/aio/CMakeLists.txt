llvmImportAsLibrary()

add_link_options(-lstdc++fs -lrt)
llvmLinkLibrary()

add_executable(misc.aio aio.cpp ${files.share.aio} ${files.share.io})
