//
// Created by Khyber on 7/18/2019.
//

#include "src/share/llvm/operandBundles.h"

namespace llvm {
    
    ArrayRef<OperandBundleDef> getOperandBundles(const CallBase& inst) noexcept {
        return {reinterpret_cast<const OperandBundleDef*>(inst.bundle_op_info_begin()), inst.getNumOperandBundles()};
    }
    
}
