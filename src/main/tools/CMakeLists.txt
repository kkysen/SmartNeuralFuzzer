llvmImportAsLibrary()

files(klang
        Program.h
        Program.cpp
        klang.cpp)

set(files.share ${files.share.common} ${files.share.stde})

add_executable(klang ${files.klang})
