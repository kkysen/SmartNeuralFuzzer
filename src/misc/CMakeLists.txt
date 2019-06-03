llvmImportAsLibrary()

set(files.share ${files.share.aio} ${files.share.io})

add_link_options(-lrt -pthread -ltinfo)
add_link_options("-L${llvm.lib.dir}" -lLLVMSupport)

add_executable(aio aio.cpp ${files.share})

add_executable(signalHandlerInception signalHandlerInception.cpp)
add_executable(rt_sigqueueinfo rt_sigqueueinfo.cpp)
add_executable(repeatedSigqueue repeatedSigqueue.cpp)
add_executable(tid tid.cpp)
add_executable(stdListIteratorInvalidation stdListIteratorInvalidation.cpp)
