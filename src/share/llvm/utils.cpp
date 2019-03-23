//
// Created by Khyber on 3/23/2019.
//

#include "src/share/llvm/utils.h"

namespace llvm {
    
    std::string uuid(const BasicBlock& block) {
        std::string s;
        raw_string_ostream out(s);
        block.printAsOperand(out, false);
        return out.str();
    }
    
}
