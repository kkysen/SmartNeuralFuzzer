//
// Created by Khyber on 4/8/2019.
//

#include "src/main/pass/register/register.h"

namespace llvm::pass {
    
    void addGlobalExtension(ExtensionPoint extensionPoint, ExtensionFunc extensionFunc) {
        // the conversion from a raw function pointer to a std::function happens here
        // this file only will be preloaded (LD_PRELOAD) in front of opt/clang,
        // so that it is not unloaded (like pass plugins) before std::function<>~function() runs
        // when the actual destructor function has been unloaded
        PassManagerBuilder::addGlobalExtension(extensionPoint, extensionFunc);
    }
    
}