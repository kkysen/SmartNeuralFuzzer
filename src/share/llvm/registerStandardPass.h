//
// Created by Khyber on 3/28/2019.
//

#pragma once

#include "llvm/PassRegistry.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

namespace llvm::pass {
    
    using ExtensionPoint = PassManagerBuilder::ExtensionPointTy;
    
    template <class Pass>
    bool registerStandard(ArrayRef<ExtensionPoint> extensionPoints) {
        for (auto&& extensionPoint : extensionPoints) {
            RegisterStandardPasses(extensionPoint, [](auto&, auto& pm) { pm.add(new Pass()); });
        }
        return true;
    }
    
    template <class Pass>
    bool registerStandardAlwaysLast() {
        return registerStandard<Pass>({ExtensionPoint::EP_OptimizerLast, ExtensionPoint::EP_EnabledOnOptLevel0});
    }
    
}
