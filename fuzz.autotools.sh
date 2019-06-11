#!/bin/bash

originalLDFlagsCache=originalLDFLAGS.txt

clean() {
    local target=${1}
    local what=${2}

    local bc=${target}.0.6.coverage.bc
    local o=${target}.coverage.o
    local exe=${target}.coverage
    rm -f ${bc} ${o} ${exe} *.blocks.map

    if [[ "${what}" == "coverage" ]]; then
        return
    fi

    rm -f ${target}.*
    make clean

    if [[ "${what}" == "all" ]]; then
        rm -f ${originalLDFlagsCache}
    fi
}

fuzz() {

    if [[ $# == 0 ]]; then
        echo "usage: ${0} <target executable>"
        return 1
    fi
    local target=${1}
    local clean=${2}
    if [[ "${clean}" == "-clean" ]]; then
        clean ${target} ${3}
        return
    fi

    # exit when any command fails
    set -e

    # keep track of the last executed command
    local currentCommand=
    local lastCommand=
    trap 'echo "\"${lastCommand}\" command filed with exit code $?."' EXIT
    trap 'local lastCommand=${currentCommand}; local currentCommand=${BASH_COMMAND}' DEBUG
    # echo an error message before exiting

    local flto="-flto -fuse-ld=lld" # flto makes .o files .bc files
    local myLDFLAGS="${flto} -Wl,-plugin-opt=save-temps" # generates .bc files also

	local cc=clang
	local cxx=clang++
	local ranlib=llvm-ranlib
	local cFlags=" -flto ${CFLAGS} "
	local ldFlags=" ${myLDFLAGS} ${LDFLAGS} "

    if [[ -f "${originalLDFlagsCache}" ]]; then
        true
    else
        # only run configure once
        CC=${cc} CXX=${cxx} RANLIB=${ranlib} CFLAGS=${cFlags} LDFLAGS=${ldFlags} ./configure
        rm -f a.out.* # generated by autotools for testing
        # need these for final link
        make -n | tail -n 1 | sed 's/.*'"${myLDFLAGS}"'//' > "${originalLDFlagsCache}"
    fi
    local originalLDFLAGS=$(cat "${originalLDFlagsCache}")

    make -j$(getconf _NPROCESSORS_ONLN)

    # TODO runtimes should use flto, so they should be LLVM bitcode, not object files

    local projectDir=~/workspace/sync/SmartNeuralFuzzer
    local buildDir=${projectDir}/build
    local libDir=${buildDir}/lib
    local binDir=${buildDir}/bin
    local register=${libDir}/libpass.register.so
    local block=${libDir}/libpass.coverage.block.so
    local branch=${libDir}/libpass.coverage.block.so
    local passes="${block} ${branch}"
    local loadPasses="-load=${block} -load=${branch}"
    local runtimes="${libDir}/libruntime.coverage.block.a ${libDir}/libruntime.coverage.branch.a"
    local src=${target}.0.5.precodegen.bc
    local dependencies="${src} ${passes}"
    local bc=${target}.0.6.coverage.bc
    local obj=${target}.coverage.o
    local exe=${target}.coverage
    local libraries="-lstdc++ -lstdc++fs -pthread -ldl -L${CLANG_HOME}/lib -lLLVMSupport"
    local opt=${binDir}/opt-9
    local optArgs="-O3 ${loadPasses} ${src}"
    local linkDependencies=${runtimes}
    local linkArgs="${flto} ${obj} ${linkDependencies} ${libraries} ${originalLDFLAGS}"

	local dir=$(dirname "${0}")
	ninja -C ${dir}/build main

    # optimize (instrument), compile bc to obj, and then link everything
    # TODO this shouldn't have to be -O3

    # I put these commands in a Makefile instead to cache things.
#    ${opt} ${optArgs} -o ${bc}
#    ${cc} ${bc} -c -o ${obj}
#    ${cc} ${linkArgs} -o ${exe}

	bc=${bc} obj=${obj} exe=${exe} \
	cc=${cc} opt=${opt} \
	dependencies=${dependencies} linkDependencies=${linkDependencies} \
	optArgs=${optArgs} linkArgs=${linkArgs} \
	make -f ${dir}/AutotoolsMakefile

}

fuzz "$@"
