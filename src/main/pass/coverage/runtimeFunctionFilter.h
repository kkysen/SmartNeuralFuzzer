//
// Created by Khyber on 5/21/2019.
//

#pragma once

#include <src/share/llvm/BinaryFunctionFilter.h>

namespace llvm::pass::coverage {
    
    const BinaryFunctionFilter& runtimeFunctionFilter();
    
}
