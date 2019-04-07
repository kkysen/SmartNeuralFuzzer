//
// Created by Khyber on 4/7/2019.
//

#include "src/main/runtime/RuntimeOutput.h"

namespace runtime {
    
    std::string RuntimeOutput::getDirName(std::string_view name) {
        using namespace std::string_literals;
        return (((""s += name) += ".out.") += std::to_string(getpid())) += ".dir";
    }
    
    RuntimeOutput::RuntimeOutput(std::string_view name) noexcept
            : name(name), dir(fse::Dir().dir(getDirName(name))) {}
    
}
