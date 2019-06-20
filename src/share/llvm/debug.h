//
// Created by Khyber on 3/16/2019.
//

#pragma once

#include "src/share/common/debug.h"
#include "src/share/llvm/utils.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/BasicBlock.h"

namespace llvm {
    
    raw_ostream& operator<<(raw_ostream& out, bool boolean);
    
    raw_ostream& operator<<(raw_ostream& out, std::string_view view);
    
    std::string_view to_string_view(Type::TypeID typeId);
    
    raw_ostream& operator<<(raw_ostream& out, Type::TypeID typeId);
    
    template <typename A, typename B>
    raw_ostream& operator<<(raw_ostream& out, const std::pair<A, B>& pair) {
        const auto& [a, b] = pair;
        return out << "(" << a << ", " << b << ")";
    }
    
}

#define llvm_debug() _debug(llvm::errs())

#define llvm_dbg(expr) llvm_debug()(_expr(expr))
