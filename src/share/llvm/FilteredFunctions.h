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
        bool forEachFunction(F onFunction) {
            bool modified = false;
            for (auto& function : module) {
                if (function.empty() || filter(function.getName())) {
                    continue;
                }
                if (onFunction(function)) {
                    modified = true;
                }
            }
            return modified;
        }
    
        template <class F, class G, class H>
        bool forEach(F onBlock, G preFunction, H postFunction) {
            return forEachFunction([&](auto& function) {
                preFunction(function);
                bool modified = false;
                for (auto& block : function) {
                    if (onBlock(block)) {
                        modified = true;
                    }
                }
                postFunction(function, modified);
                return modified;
            });
        }
        
        template <class F, class G>
        bool forEach(F onBlock, G preFunction) {
            return forEach(onBlock, preFunction, [](auto&&, auto&&) {});
        }
    
        template <class F>
        bool forEach(F onBlock) {
            return forEach(onBlock, [](auto&&) {});
        }
        
        template <class F>
        bool forEachBlock(F onBlock) {
            return forEach(onBlock);
        }
        
    };
    
}
