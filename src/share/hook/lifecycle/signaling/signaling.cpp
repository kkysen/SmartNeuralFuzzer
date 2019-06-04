//
// Created by Khyber on 6/3/2019.
//

#include "src/share/hook/lifecycle/signaling/signaling.h"

#include <random>

namespace {
    
    u64 getRandomMagicNumber() noexcept {
        return std::random_device()();
    }
    
}

namespace hook::lifecycle::signaling::constants {
    
    u64 magicNumber = getRandomMagicNumber();
    
}
