//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include "llvm/IR/BasicBlock.h"

namespace llvm {
    
    std::string uuid(BasicBlock& block) {
        std::string s;
        raw_string_ostream out(s);
        block.printAsOperand(out, false);
        return out.str();
    }
    
}
