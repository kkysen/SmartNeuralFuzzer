#!/bin/bash

fuzz() {
	# exit when any command fails
    set -e

    # keep track of the last executed command
    local currentCommand=
    local lastCommand=
    trap 'echo "\"${lastCommand}\" command filed with exit code $?."' EXIT
    trap 'lastCommand=${currentCommand}; currentCommand=${BASH_COMMAND}' DEBUG
    # echo an error message before exiting

	if [[ -x opt-9 ]]; then
		echo "opt-9 is not installed"
		exit 1
	fi

	local name=${__name}

	if [[ ! -d "${name}" ]]; then
		mkdir ${name}
	fi
	cd ${name}

	local urlBase="http://ftpmirror.gnu.org/${name}"
	local tarFileName=$(wget -qO- ${urlBase} \
		| sed -e s/.*href=\"// \
		| sed -e s/\"\>.*// \
		| grep "${name}.*\.tar\.*" \
		| grep -vE ".sig" \
		| sort --version-sort \
		| tail -n 1
	)
	local url="${urlBase}/${tarFileName}"
	local fileName=$(echo ${tarFileName} | sed -e s/\.tar\..*//)

	if [[ ! -f "${tarFileName}" ]]; then
		wget ${url}
	fi
	if [[ ! -d "${fileName}" ]]; then
		tar xf ${tarFileName}
	fi
	cd ${fileName}

	local srcDir=${__srcDir}
	local binDir=${__buildDir}/bin

	local ldFlagsFile=${srcDir}/LDFLAGS/${name}
	if [[ -f "${ldFlagsFile}" ]]; then
		cp ${ldFlagsFile} __LDFLAGS.txt
	fi

	${binDir}/fuzz.autotools "$@"
}

fuzz "$@"
