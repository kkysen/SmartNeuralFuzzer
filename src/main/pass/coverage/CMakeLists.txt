llvmImportAsRuntime()

set(files.share ${files.share.common} ${files.share.llvm})

add_subdirectory(branch)
add_subdirectory(block)
