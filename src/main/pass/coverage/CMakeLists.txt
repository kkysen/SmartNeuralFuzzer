llvmImportAsRuntime()

set(files.share ${files.share.common} ${files.share.llvm})

add_subdirectory(branch)
add_subdirectory(block)

add_custom_target(pass.coverage)
add_dependencies(pass.coverage pass.coverage.branch pass.coverage.block)
