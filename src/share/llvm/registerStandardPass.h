//
// Created by Khyber on 3/28/2019.
//

#pragma once

#include "llvm/PassRegistry.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

namespace llvm::pass {
    
    using ExtPt = PassManagerBuilder::ExtensionPointTy;
    
    template <class Pass>
    bool registerStandard(ArrayRef<ExtPt> extensionPoints) {
        for (auto&& extensionPoint : extensionPoints) {
            RegisterStandardPasses(extensionPoint, [](auto&, auto& pm) { pm.add(new Pass()); });
        }
        return true;
    }
    
    template <class Pass>
    bool registerStandardAlwaysLast() {
        return registerStandard<Pass>({ExtPt::EP_OptimizerLast, ExtPt::EP_EnabledOnOptLevel0});
    }
    
}
