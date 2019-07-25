llvmImportAsLibrary()

set(libraries -lstdc++fs -ldl ${llvm.link.libs})
string(REPLACE ";" " " libraries "${libraries}")

add_compile_definitions(BIN_PATH_FUZZ_AUTOTOOLS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")
add_compile_definitions(RUNTIME_COVERAGE_LIBRARIES=\"${libraries}\")

set(fuzzers autotools gnu.utils)
foreach (fuzzer ${fuzzers})
    set(target tool.fuzz.${fuzzer})
    add_executable(${target} fuzz.${fuzzer}.cpp)
    copyExecutable(${target})
endforeach ()

function(alias name alias)
    aliasBin(tool.fuzz.${name} bin fuzz.${alias})
endfunction()

alias(autotools autotools)
alias(gnu.utils binutils)
alias(gnu.utils coreutils)
