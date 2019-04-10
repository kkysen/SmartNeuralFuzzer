#!/bin/bash bash

setLdPreload() {
    export LD_PRELOAD=/home/khyber/workspace/sync/SmartNeuralFuzzer/build/src/main/pass/register/libpass.register.so
}

unsetLdPreload() {
    export LD_PRELOAD=
}
