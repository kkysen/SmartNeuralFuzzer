//
// Created by Khyber on 6/10/2019.
//

#pragma once

#include "src/share/llvm/lib/BinaryFunctionFilter.h"

#include "llvm/IR/Module.h"

namespace llvm::pass {
    
    struct FilteredFunctions {
    
        const BinaryFunctionFilter& filter;
        Module& module;
        
        template <class F>
        bool forEachFunction(F f) {
            bool modified = false;
            for (auto& function : module) {
                if (function.empty() || filter(function.getName())) {
                    continue;
                }
                if (f(function)) {
                    modified = true;
                }
            }
            return modified;
        }
    
        template <class F, class G>
        bool forEach(F f, G g) {
            return forEachFunction([&](auto& function) {
                g(function);
                bool modified = false;
                for (auto& block : function) {
                    if (f(block)) {
                        modified = true;
                    }
                }
                return modified;
            });
        }
        
        template <class F>
        bool forEachBlock(F f) {
            return forEach(f, [](auto&) {});
        }
        
    };
    
}
