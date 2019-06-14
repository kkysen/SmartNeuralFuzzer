set(target tool.preload.pass.register)
add_executable(${target} preloadPassRegister.cpp ../../../share/io/env/LdPreload.cpp)
copyExecutable(${target})

function(alias _alias)
    aliasBin(${target} bin ${_alias})
endfunction()

alias(clang-${llvmVersionMajorNewest})
alias(opt-${llvmVersionMajorNewest})
