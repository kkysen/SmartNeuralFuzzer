#!/bin/bash

buildDir=${__buildDir}
srcDir=${__srcDir}
libraries=${__libraries}

originalLDFlagsCache=__LDFLAGS.txt

cc=clang
cxx=clang++
flto="-flto -fuse-ld=lld" # flto makes .o files .bc files
myLDFLAGS="${flto} -Wl,-plugin-opt=save-temps" # generates .bc files also

clean() {
	echo "clean not implemented yet"
	exit 1

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

runNinja() {
	ninja -C ${buildDir} main
}

configure() {
	local ranlib=llvm-ranlib
	local cFlags=" -flto ${CFLAGS} "
	local ldFlags=" ${myLDFLAGS} ${LDFLAGS} "
	CC=${cc} CXX=${cxx} RANLIB=${ranlib} CFLAGS=${cFlags} LDFLAGS=${ldFlags} ./configure
}

removeADotOut() {
	rm -f $(find . -name "a.out.*")
}

configureCached() {
	local lock="configure.lock"
	if [[ ! -f "${lock}" ]]; then
	    # only run configure once
		configure
		touch ${lock}
	fi
	removeADotOut
}

findOriginalLDFlags() {
	# need these for final link
    make -n | tail -n 1 | sed 's/.*'"${myLDFLAGS}"'//' > "${originalLDFlagsCache}"
}

runMake() {
	make -j$(getconf _NPROCESSORS_ONLN) ${1}
}

compileTarget() {
	local target=${1}
	local originalLDFlags=${2}

    local libDir=${buildDir}/lib
    local binDir=${buildDir}/bin
    local register=${libDir}/libpass.register.so
    local block=${libDir}/libpass.coverage.block.so
    local branch=${libDir}/libpass.coverage.branch.so
    local passes="${block} ${branch}"
    local loadPasses="-load=${block} -load=${branch}"
#    local loadPasses="-load=${branch}"
    local runtimes=${libDir}/libruntime.coverage.bc
    local src=${target}.0.5.precodegen.bc
    local dependencies="${src} ${passes}"
    local bc=${target}.0.6.coverage.bc
    local all=${target}.coverage.bc
    local obj=${target}.coverage.o
    local exe=${target}.coverage
    local opt=${binDir}/opt-9
    local link=llvm-link
    local optLevel=-O3
    local optArgs="${loadPasses} ${src}"
    local linkArgs="${flto} ${obj} ${libraries} ${originalLDFlags}"

    # optimize (instrument), compile bc to obj, and then link everything
    # TODO this shouldn't have to be -O3

	bc=${bc} all=${all} obj=${obj} exe=${exe} \
	cc=${cxx} opt=${opt} link=${link} \
	dependencies=${dependencies} \
	optLevel=${optLevel} optArgs=${optArgs} \
	runtimes=${runtimes} linkArgs=${linkArgs} \
	make -f ${srcDir}/FuzzMakefile

	local sourceMapExt=blocks.map
	local tempBlocksSourceMap=ld-temp.o.${sourceMapExt}
	if [[ -f "${tempBlocksSourceMap}" ]]; then
    	mv ${tempBlocksSourceMap} ${target}.${sourceMapExt}
	fi
}

compileAllTargetsMatching() {
	local pattern=${1}
	local originalLDFlags=${2}
	local targetSuffix=".0.5.precodegen.bc"
	local targets=$(find . -name "${pattern}${targetSuffix}" \
		| sed -e s/${targetSuffix}// \
		| grep -vE "*.so" \
	)
	for target in ${targets}; do
		compileTarget ${target} "${originalLDFlags}" &
	done
	wait
}

compileAllTargets() {
	local originalLDFlags=${1}
	compileAllTargetsMatching "*" "${originalLDFlags}"
}

usage() {
	echo "usage: ${0} [-clean [coverage | all]]"
	exit 1
}

compile() {
	local target=${1}

	runNinja
	configureCached

	local originalLDFlags=""
    if [[ ! -f "${originalLDFlagsCache}" ]]; then
       	findOriginalLDFlags
    fi
    originalLDFlags=$(cat "${originalLDFlagsCache}")

	# it's easier just to re-make all targets
	# this shouldn't happen (i.e. not cached) very often
	runMake

	if [[ "${target}" == "" ]]; then
		compileAllTargets "${originalLDFlags}"
	else
		compileAllTargetsMatching ${target} "${originalLDFlags}"
	fi
}

fuzz() {
	# exit when any command fails
    set -e

    # keep track of the last executed command
    local currentCommand=
    local lastCommand=
    trap 'echo "\"${lastCommand}\" command filed with exit code $?."' EXIT
    trap 'lastCommand=${currentCommand}; currentCommand=${BASH_COMMAND}' DEBUG
    # echo an error message before exiting

    if [[ "${1}" == "-h" ]]; then
    	usage
    elif [[ "${1}" == "-help" ]]; then
    	usage
    elif [[ "${1}" == "--help" ]]; then
    	usage
    elif [[ "${1}" == "-c" ]]; then
    	clean "${2}" "${3}"
    elif [[ "${1}" == "-clean" ]]; then
    	clean "${2}" "${3}"
    elif [[ "${1}" == "--clean" ]]; then
    	clean "${2}" "${3}"
    else
    	compile "${1}"
    fi
}

fuzz "$@"
