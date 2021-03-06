#!/bin/bash

buildDir="${__buildDir}"
srcDir="${__srcDir}"
libraries="${__libraries}"

originalLDFlagsCache="__LDFLAGS.txt"

debug=".Debug"
clang="clang-9${debug}"

cc="${clang}"
cxx="${clang} --driver-mode=g++"
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

compileTargetWithPass() {
	local passName=${1}
	local target=${2}
	local originalLDFlags=${3}

	local name="coverage.${passName}"
	local pass="pass.${name}"

	local libDir="${buildDir}/lib"
	local binDir="${buildDir}/bin"
	local passLib="${libDir}/lib${pass}.so"
	local loadPass="-load=${passLib} -${pass}"
	local runtime="${libDir}/libruntime.${name}.bc"
	local src="${target}.0.5.precodegen.bc"
    local dependencies="${src} ${passLib}"
    local bc="${target}.0.6.${name}.bc"
    local all="${target}.${name}.bc"
    local allOpt="${target}.${name}.opt.bc"
    local obj="${target}.${name}.o"
    local exe="${target}.${name}"
    local opt="opt-9${debug}"
    local link="llvm-link"
    local optLevel="-O3"
    local optArgs="${loadPass} ${src}"
    local linkArgs="${flto} ${obj} ${libraries} ${originalLDFlags}"

    # optimize (instrument), compile bc to obj, and then link everything

	bc=${bc} all=${all} allOpt=${allOpt} obj=${obj} exe=${exe} \
	cc=${cxx} opt=${opt} link=${link} \
	dependencies=${dependencies} \
	optLevel=${optLevel} optArgs=${optArgs} \
	runtimes=${runtime} linkArgs=${linkArgs} \
	make -f ${srcDir}/FuzzMakefile
}

compileTarget() {
	local target=${1}
	local originalLDFlags=${2}

	local passes="block edge branch branch.execute"
	for pass in ${passes}; do
		compileTargetWithPass ${pass} ${target} ${originalLDFlags} &
	done
	wait

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
