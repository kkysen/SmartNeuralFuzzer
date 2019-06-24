//
// Created by Khyber on 6/21/2019.
//

#pragma once

#include "src/share/common/numbers.h"

#include "src/share/lib/corrade/CorradeArrayView.h"

#include "llvm/ADT/SmallVector.h"

using Corrade::Containers::ArrayView;

namespace {
    
    template <class T, class MakeRange, class F>
    void dfs(T t, llvm::SmallVectorImpl<T>& stack, MakeRange makeRange, F f) {
        stack.emplace_back(t);
        if (f(ArrayView(stack.data(), stack.size()))) {
            for (T e : makeRange(t)) {
                dfs(e, stack, makeRange, f);
            }
        }
        stack.pop_back();
    }
    
}

namespace stde {
    
    template <class T, class MakeRange, class F>
    void dfs(T t, MakeRange makeRange, F f) {
        llvm::SmallVector<T, 8> stack;
        ::dfs(t, stack, makeRange, f);
    }
    
}
