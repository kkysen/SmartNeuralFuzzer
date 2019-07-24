files(pass.coverage.branch
        SwitchCaseSuccessors.h
        SwitchCaseSuccessors.cpp
        )

set(files.share ${files.pass.coverage.branch} ${files.share})

add_subdirectory(main)
add_subdirectory(execute)
add_subdirectory(execute2)
