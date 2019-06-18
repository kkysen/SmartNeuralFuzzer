function(misc target)
    add_executable(misc.${target} ${ARGN})
    copyExecutable(misc.${target})
endfunction()

add_subdirectory(aio)
add_subdirectory(thread)

misc(signalHandlerInception signalHandlerInception.cpp)
misc(rt_sigqueueinfo rt_sigqueueinfo.cpp)
misc(stdListIteratorInvalidation stdListIteratorInvalidation.cpp)
misc(reboot reboot.cpp ${files.share.capability} ${files.share.hook.libc.syscall})
misc(prctlReturnErrno prctlReturnErrno.cpp)
misc(signalOrder signalOrder.cpp)

add_link_options(-lstdc++fs)

add_compile_options(-O3)

misc(deltaVarintEncoding deltaVarintEncoding.cpp ${files.share.io})
misc(bitStats bitStats.cpp ${files.share.io})
misc(counts counts.cpp)

add_custom_target(misc DEPENDS
        misc.aio
        misc.rt_sigqueueinfo
        misc.repeatedSigqueue
        misc.tid
        misc.stdListIteratorInvalidation
        misc.reboot
        misc.prctlReturnErrno
        misc.signalOrder
        misc.deltaVarintEncoding
        misc.bitStats
        misc.counts
        )
