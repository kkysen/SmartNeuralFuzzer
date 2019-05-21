//
// Created by Khyber on 5/21/2019.
//

#include "src/main/pass/BinaryFunctionFilter.h"

#include "src/share/common/debug.h"

int main() {
    using llvm::pass::BinaryFunctionFilter;
    BinaryFunctionFilter skipRuntimeFunctions;
    _dbg("");
    skipRuntimeFunctions.add(fs::path("src/main/runtime/coverage/block/libruntime.coverage.block.a"));
    return static_cast<int>(skipRuntimeFunctions(""));
}
