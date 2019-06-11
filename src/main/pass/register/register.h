//
// Created by Khyber on 4/8/2019.
//

#pragma once

#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/LegacyPassManager.h"

namespace llvm::pass {
    
    using ExtensionPoint = PassManagerBuilder::ExtensionPointTy;
    
    using ExtensionFunc = void(const PassManagerBuilder&, legacy::PassManagerBase&);
    
    /**
     * passes should call this instead of either of these:
     *      PassManagerBuilder::addGlobalExtension
     *      RegisterStandardPasses::RegisterStandardPasses
     */
    void addGlobalExtension(ExtensionPoint extensionPoint, ExtensionFunc extensionFunc);
    
}

namespace llvm::pass::register_ {



}
