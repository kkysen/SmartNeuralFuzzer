//
// Created by Khyber on 3/28/2019.
//

#pragma once

#include "src/main/pass/register/register.h"

#include "llvm/PassRegistry.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

namespace llvm::pass {
    
    using ExtPt = PassManagerBuilder::ExtensionPointTy;
    
    template <class Pass>
    void registerStandard(const PassManagerBuilder&, legacy::PassManagerBase& pm) {
        pm.add(new Pass());
    }
    
    template <class Pass>
    bool registerStandard(ArrayRef<ExtPt> extensionPoints, ExtensionFunc func = registerStandard<Pass>) {
        for (auto&& extensionPoint : extensionPoints) {
            addGlobalExtension(extensionPoint, func);
        }
        return true;
    }
    
    std::array<ExtPt, 2> alwaysLast = {ExtPt::EP_OptimizerLast, ExtPt::EP_EnabledOnOptLevel0};
    
    template <class Pass>
    bool registerStandardAlwaysLast() {
        return registerStandard<Pass>(alwaysLast);
    }
    
}
