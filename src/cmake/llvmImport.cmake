function(llvmImport asLibrary)
    llvmConfig(includedir llvmIncludes)
    include_directories(SYSTEM "${llvmIncludes}")
    llvmConfig(prefix llvmPrefix)
    include_directories(SYSTEM "${llvmPrefix}/include")
    
    llvmConfig(cxxflags llvmFlags)
    string(REGEX REPLACE "-std=[^ ]*" "" llvmFlags "${llvmFlags}")
    
#    if (${llvmVersionMajorIsNewest})
#
#    else ()
#        include_directories(SYSTEM "${CXX_LIBS}/llvm-project/llvm/include/")
#        include_directories(SYSTEM "${CXX_LIBS}/llvm-project/build/clang/fewTargets/Release/include/")
#
#        set(llvmMacros "-D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS")
#        set(llvmExceptions "-fno-exceptions -fno-rtti")
#        set(llvmFlags "${llvmExceptions} ${llvmMacros}")
#    endif ()
    
    if (${asLibrary})
        string(REPLACE "-fno-exceptions" "" llvmFlags "${llvmFlags}")
        string(REPLACE "-fno-rtti" "" llvmFlags "${llvmFlags}")
    endif ()
    
    #add_compile_options(${llvmFlags})  # doesn't keep -fno-rtti so typeinfo methods are created
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${llvmFlags}" PARENT_SCOPE)
endfunction()

function(llvmImportAsLibrary)
    llvmImport(TRUE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" PARENT_SCOPE)
endfunction()

function(llvmImportAsRuntime)
    llvmImport(FALSE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" PARENT_SCOPE)
endfunction()

function(llvmPreloadPassRegister)
    set(ENV{LD_PRELOAD} "$ENV{LD_PRELOAD} ${CMAKE_CURRENT_BINARY_DIR}/src/main/pass/register/libpass.register.so")
endfunction()
