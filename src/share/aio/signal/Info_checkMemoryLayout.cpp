//
// Created by Khyber on 5/26/2019.
//

#include "src/share/aio/signal/Info.h"

#include <random>
#include <functional>

namespace aio::signal {
    
    std::pair<bool, std::string_view> Info::memoryLayoutMatchesSigInfoT(size_t trials) noexcept {
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<char> distribution;
        const auto random = std::bind(distribution, generator);
        siginfo_t sigInfo = {};
        char* data = reinterpret_cast<char*>(&sigInfo);
        for (size_t i = 0; i < trials; i++) {
            std::generate(data, data + sizeof(sigInfo), random);
            const auto [matches, message] = memoryLayoutMatchesSigInfoT(sigInfo, of(sigInfo));
            if (!matches) {
                return {matches, message};
            }
        }
        return {true, ""};
    }
    
    bool Info::checkMemoryLayoutMatchesSigInfoT(size_t trials) {
        const auto [matches, message] = memoryLayoutMatchesSigInfoT(trials);
        if (matches) {
            return true;
        }
        throw std::logic_error(std::string(message));
    }
    
}

namespace {
    
    using aio::signal::Info;
    
    [[maybe_unused]] const bool unused = Info::checkMemoryLayoutMatchesSigInfoT();
    
}
