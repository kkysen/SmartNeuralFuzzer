//
// Created by Khyber on 7/15/2019.
//

#pragma once

#include "src/share/llvm/IRBuilderExt.h"

#include "llvm/IR/CFG.h"

namespace llvm::pass::coverage::branch {
    
    class SwitchCaseSuccessors {
    
    private:
        
        using BlockSet = SmallPtrSet<BasicBlock*, 8>;
        
        BlockSet successors;
    
    public:
        
        constexpr u32 numBranches() const noexcept {
            return successors.size();
        }
        
        constexpr const BlockSet& get() const noexcept {
            return successors;
        }
        
        void findUniqueBranches(SwitchInst& switchInst);
        
        bool hasFallThroughCases(BasicBlock& switchBlock) const;
        
        Value& createValidPtr(SwitchInst& switchInst) const;
        
    };
    
}
