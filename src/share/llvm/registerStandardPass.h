//
// Created by Khyber on 3/28/2019.
//

#pragma once

#include "src/share/llvm/debug.h"

#include "llvm/PassRegistry.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

namespace llvm::pass {
    
    using ExtPt = PassManagerBuilder::ExtensionPointTy;
    
    template <class Pass>
    bool registerStandard(ArrayRef<ExtPt> extensionPoints) {
        llvm_dbg("start");
        for (auto&& extensionPoint : extensionPoints) {
            llvm_dbg(extensionPoint);
            RegisterStandardPasses(extensionPoint, [](const auto&, auto& pm) {
                llvm_dbg("callback");
                pm.add(new Pass());
            });
        }
        llvm_dbg("end");
        return true;
    }
    
    template <class Pass>
    bool registerStandardAlwaysLast() {
//        return registerStandard<Pass>({ExtPt::EP_OptimizerLast, ExtPt::EP_EnabledOnOptLevel0});
        return registerStandard<Pass>({}); // any EPs I've tried have caused segfaults
    }
    
}
