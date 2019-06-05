add_subdirectory(aio)
add_subdirectory(thread)

add_executable(misc.signalHandlerInception signalHandlerInception.cpp)
add_executable(misc.rt_sigqueueinfo rt_sigqueueinfo.cpp)
add_executable(misc.stdListIteratorInvalidation stdListIteratorInvalidation.cpp)
add_executable(misc.reboot reboot.cpp ${files.share.capability})
add_executable(misc.prctlReturnErrno prctlReturnErrno.cpp)
add_executable(misc.signalOrder signalOrder.cpp)

add_custom_target(misc DEPENDS
        misc.aio
        misc.rt_sigqueueinfo
        misc.repeatedSigqueue
        misc.tid
        misc.stdListIteratorInvalidation
        misc.reboot
        )
