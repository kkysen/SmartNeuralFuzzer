//
// Created by Khyber on 5/21/2019.
//

#include "src/main/pass/coverage/runtimeFunctionFilter.h"

namespace {
    
    using llvm::pass::BinaryFunctionFilter;
    
    std::atomic<bool> initialized = false;
    BinaryFunctionFilter filter;
    
}

namespace llvm::pass::coverage {
    
    const BinaryFunctionFilter& runtimeFunctionFilter() {
        if (initialized.exchange(true)) {
            return filter;
        }
        constexpr std::string_view paths[] = {BIN_PATH_RUNTIME_COVERAGE};
        for (const auto path : paths) {
            filter.add(fs::path(path));
        }
        return filter;
    }
    
    FilteredFunctions filteredFunctions(Module& module, const BinaryFunctionFilter& filter) {
        return {.filter = filter, .module = module};
    }
    
}
