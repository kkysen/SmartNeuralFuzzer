#!/bin/bash

find() {
    local typeParts=(${1//./ })
    local type=${typeParts[0]}
    local ext=${typeParts[1]}
    local prefix=$2
    for value in "${@:3}"; do
        echo "${prefix}/src/main/${type}/coverage/${value}/lib${type}.coverage.${value}.${ext}"
    done
}

find $@
