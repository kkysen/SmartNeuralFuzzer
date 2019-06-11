//
// Created by Khyber on 5/21/2019.
//

#include "src/share/llvm/lib/conversions.h"

namespace llvm::convert {
    
    std::string_view view(StringRef ref) noexcept {
        return std::string_view(ref.data(), ref.size());
    }
    
}