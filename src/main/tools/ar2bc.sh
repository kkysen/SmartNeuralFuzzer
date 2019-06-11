#!/bin/bash

ar2bc() {
	set -e

	local target=${1}
	local archive=lib${target}.a
	local bc=lib${target}.bc
	local tempDir=${$}
	mkdir ${tempDir}
	trap 'rm -rf ${tempDir}' EXIT
	cd ${tempDir}
	llvm-ar x ../${archive}
	llvm-link ./* -o ../${bc}
	cd ..
	exit
}

ar2bc "$@"
