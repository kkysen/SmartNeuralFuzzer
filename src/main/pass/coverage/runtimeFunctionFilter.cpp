//
// Created by Khyber on 5/21/2019.
//

#include "src/main/pass/coverage/runtimeFunctionFilter.h"

namespace {
    
    using llvm::pass::BinaryFunctionFilter;
    
    bool initialized = false;
    BinaryFunctionFilter filter;
    
}

namespace llvm::pass::coverage {
    
    const BinaryFunctionFilter& runtimeFunctionFilter() {
        if (initialized) {
            return filter;
        }
        initialized = true;
        constexpr std::string_view paths[] = {BIN_PATH_RUNTIME_COVERAGE_BLOCK, BIN_PATH_RUNTIME_COVERAGE_BRANCH};
        for (auto path : paths) {
            filter.add(fs::path(path));
        }
        return filter;
    }
}
