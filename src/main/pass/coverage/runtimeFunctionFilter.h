//
// Created by Khyber on 5/21/2019.
//

#pragma once

#include "src/share/llvm/FilteredFunctions.h"

namespace llvm::pass::coverage {
    
    const BinaryFunctionFilter& runtimeFunctionFilter();
    
    FilteredFunctions filteredFunctions(Module& module, const BinaryFunctionFilter& filter = runtimeFunctionFilter());
    
}
