//
// Created by Khyber on 7/15/2019.
//

#include "src/main/pass/coverage/branch/SwitchCaseSuccessors.h"

namespace llvm::pass::coverage::branch {
    
    // each branch can have multiple cases
    // i.e., multiple cases can go to the same successor block,
    // but it's only 1 real branch in that case
    void SwitchCaseSuccessors::findUniqueBranches(SwitchInst& switchInst) {
        BasicBlock* successor = switchInst.case_default()->getCaseSuccessor();
        if (successor) {
            successors.insert(successor);
        }
        const BasicBlock* lastSuccessor = successor;
        for (const auto& caseHandle : switchInst.cases()) {
            BasicBlock* successor = caseHandle.getCaseSuccessor();
            // cases are usually already in order, so this is just an optimization
            if (!successor || successor == lastSuccessor) {
                continue;
            }
            successors.insert(successor);
            lastSuccessor = successor;
        }
    }
    
    // find if there are any successors with non-unique predecessors (i.e. fallthrough cases)
    // for these pairs, we need to use the onSwitchCase() API instead of just onMultiBranch()
    bool SwitchCaseSuccessors::hasFallThroughCases(BasicBlock& switchBlock) const {
        for (BasicBlock* successor : successors) {
            for (BasicBlock* predecessor : llvm::predecessors(successor)) {
                if (predecessor != &switchBlock) {
                    return true;
                }
            }
        }
        return false;
    }
    
    Value& SwitchCaseSuccessors::createValidPtr(SwitchInst& switchInst) const {
        // sometimes the default case block is jumped to from outside of the switch instruction
        // so we get an error "Instruction does not dominate all uses"
        // since the validPtr won't have been defined in that jump
        // if we insert the validPtr right before the switch instruction
        // instead, it's easier to just put it at the end of the first block of the function
        IRBuilderExt irbe(switchInst.getParent()->getParent()->front().getTerminator());
        auto& validPtr = irbe.alloca(irbe.types().get<bool>());
        irbe.store(irbe.constants().getInt(true), validPtr);
        return validPtr;
    }
    
}
