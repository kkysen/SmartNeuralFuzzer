set(target tool.opt)
add_executable(${target} opt.cpp)
copyExecutable(${target})

function(alias _alias)
    aliasBin(${target} bin ${_alias})
endfunction()

set(passes.coverage block edge branch branch.execute)
foreach (pass.coverage ${passes.coverage})
    set(pass coverage.${pass.coverage})
    alias(opt-${llvmVersionMajorNewest}.${pass})
    alias(opt.${pass})
endforeach ()
