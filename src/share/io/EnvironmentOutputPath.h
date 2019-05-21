//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include "src/share/io/fs.h"

#include <string_view>
#include <functional>

#include <unistd.h>

namespace env::path::output {
    
    using DefaultOutputPath = fs::path (*)(const std::string& defaultEnvironmentVariableName, pid_t pid);
    
    fs::path get(DefaultOutputPath defaultOutputPath, const std::string& environmentVariableName);
    
    constexpr auto getter(DefaultOutputPath defaultOutputPath) noexcept {
        return [=](auto&& var) { return get(defaultOutputPath, var); };
    }
    
}
