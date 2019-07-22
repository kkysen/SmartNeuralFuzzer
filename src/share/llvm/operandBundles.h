//
// Created by Khyber on 7/18/2019.
//

#pragma once

#include "llvm/IR/InstrTypes.h"

namespace llvm {
    
    ArrayRef<OperandBundleDef> getOperandBundles(const CallBase& inst) noexcept;
    
}
