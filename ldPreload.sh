#!/bin/bash bash

ldPreloadSet() {
    export LD_PRELOAD=/home/khyber/workspace/sync/SmartNeuralFuzzer/build/lib/libpass.register.so
}

ldPreloadUnset() {
    export LD_PRELOAD=
}
