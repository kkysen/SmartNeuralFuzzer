llvmImportAsLibrary()

set(files.share ${files.share.hooks} ${files.share.aio.signal})

add_link_options(-ldl)
llvmLinkLibrary()

add_executable(share.hooks.libc.test test.cpp ${files.share})
