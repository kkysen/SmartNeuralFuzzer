//
// Created by Khyber on 5/21/2019.
//

#pragma once

#include "llvm/ADT/StringRef.h"

#include <string_view>

namespace llvm::convert {
    
    constexpr StringRef ref(std::string_view view) noexcept {
        return StringRef(view.data(), view.size());
    }
    
    // TODO this should be constexpr since StringRef::data() should be constexpr
    // this is why std::string_view is preferred over StringRef
    /*constexpr*/ std::string_view view(StringRef ref) noexcept;
    
}
