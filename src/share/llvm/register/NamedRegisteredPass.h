//
// Created by Khyber on 7/24/2019.
//

#pragma once

#include "llvm/Pass.h"
#include "llvm/PassSupport.h"

namespace llvm::pass {
    
    template <class Pass, class PassType = ModulePass>
    class NamedRegisteredPass : public PassType {
    
    public:
        
        static char ID;
        
        NamedRegisteredPass() : PassType(ID) {}
        
        StringRef getPassName() const override {
            return Pass::name;
        }
        
        static bool register_() {
            pass.getNormalCtor();
            return true;
        }
    
    private:
        
        static RegisterPass<Pass> pass;
        
    };
    
    template <class Pass, class PassType>
    char NamedRegisteredPass<Pass, PassType>::ID = 0;
    
    template <class Pass, class PassType>
    RegisterPass<Pass> NamedRegisteredPass<Pass, PassType>::pass(PASS_NAME, Pass::name, false, false);
    
}
