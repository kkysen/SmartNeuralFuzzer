llvmImportAsLibrary()

set(files.share
        ${files.share.common}
        ${files.share.common.debug}
        ${files.share.stde}
        ${files.share.io}
        ${files.share.llvm}
        ${files.pass}
        )

#llvmConfig(libdir llvm.libdir)
#add_link_options("-L${llvm.libdir}" -lLLVMCore -lLLVMSupport)

# not sure why these are needed, they weren't before
add_link_options(-lstdc++)
add_link_options(-lstdc++fs)

set(tests
        BinaryFunctionFilter
        )
foreach (test ${tests})
    add_executable(${test} ${files.share} "${test}.cpp")
endforeach ()

add_custom_target(unitTests)
add_dependencies(unitTests ${tests})
