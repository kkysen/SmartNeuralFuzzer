llvmImportAsLibrary()

add_link_options(-lstdc++fs -lrt)
llvmLinkLibrary()

misc(aio aio.cpp ${files.share.aio} ${files.share.io})
