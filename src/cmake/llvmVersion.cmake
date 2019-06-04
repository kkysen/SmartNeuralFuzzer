set(llvmVersionMajorNewest 9)

function(llvmConfig option var)
    execute_process(
            COMMAND bash -c "source ~/.bash_path.sh; llvm-config --${option}"
            OUTPUT_VARIABLE output
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(${var} "${output}" PARENT_SCOPE)
endfunction()

llvmConfig(version llvmVersion)

string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+).*$" "\\1" llvmVersionMajor "${llvmVersion}")
string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+).*$" "\\2" llvmVersionMinor "${llvmVersion}")
string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+).*$" "\\3" llvmVersionPatch "${llvmVersion}")

string(COMPARE EQUAL ${llvmVersionMajor} ${llvmVersionMajorNewest} llvmVersionMajorIsNewest)

# doesn't have same ABI

#function(llvmGetLibDir var)
#    execute_process(
#            COMMAND bash -c "source ~/.bash_path.sh; dirname $(dirname `which clang`)"
#            OUTPUT_VARIABLE output
#            OUTPUT_STRIP_TRAILING_WHITESPACE
#    )
#    set(${var} "${output}/lib" PARENT_SCOPE)
#endfunction()
#
#llvmGetLibDir(llvm.lib.dir)

llvmConfig(libdir llvm.lib.dir)
