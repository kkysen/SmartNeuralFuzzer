llvmImportAsLibrary()

set(files.share ${files.share.common} ${files.share.io} ${files.share.aio})

add_subdirectory(branch)
add_subdirectory(block)
