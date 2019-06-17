function(llvmImport asLibrary)
    if (${llvmVersionMajorIsNewest})
        llvmConfig(includedir llvm.includes)
        include_directories(SYSTEM "${llvm.includes}")
        llvmConfig(prefix llvm.prefix)
        include_directories(SYSTEM "${llvm.prefix}/include")
        
        llvmConfig(cxxflags llvm.flags)
        string(REGEX REPLACE "-std=[^ ]*" "" llvm.flags "${llvm.flags}")
    else ()
        include_directories(SYSTEM "${files.lib.C++}/llvm-project/llvm/include/")
        include_directories(SYSTEM "${files.lib.C++}/llvm-project/build/clang/fewTargets/Release/include/")
        
        set(llvm.macros "-D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS")
        set(llvm.exceptions "-fno-exceptions -fno-rtti")
        set(llvm.flags "${llvm.exceptions} ${llvm.macros}")
    endif ()
    
    if (${asLibrary})
        string(REPLACE "-fno-exceptions" "" llvm.flags "${llvm.flags}")
        string(REPLACE "-fno-rtti" "" llvm.flags "${llvm.flags}")
    endif ()
    
    #    message("${llvm.flags}")
    
    #add_compile_options(${llvm.flags})  # doesn't keep -fno-rtti so typeinfo methods are created
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${llvm.flags}" PARENT_SCOPE)
endfunction()

function(llvmImportAsRuntime)
    llvmImport(FALSE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" PARENT_SCOPE)
endfunction()

function(llvmImportAsLibrary)
    llvmImport(TRUE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" PARENT_SCOPE)
endfunction()

set(llvm.link.libs
        -L${llvm.lib.dir} -lLLVMSupport
        -L${llvm.lib.dir} -lLLVMCore
        -pthread -ltinfo
        )

function(llvmLinkLibrary)
    llvmImportAsLibrary()
    add_link_options(${llvm.link.libs})
endfunction()
