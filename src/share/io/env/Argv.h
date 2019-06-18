//
// Created by Khyber on 6/12/2019.
//

#pragma once

#include "src/share/lib/corrade/CorradeArrayView.h"

#include "llvm/ADT/SmallVector.h"

#include <string>

namespace env {
    
    using namespace Corrade::Containers;
    
    class Argv {
        
        std::string raw;
        llvm::SmallVector<std::string_view, 5> args;
        std::string_view _programName;
    
    private:
        
        Argv(std::string raw, size_t argc);
    
        struct Key {};
        
    public:
        
        Argv(std::string raw, Key key);
        
        explicit Argv(ArrayView<std::string_view> args);
        
        Argv(int argc, const char* const* argv);
        
        static const Argv& get();
        
        constexpr size_t size() const noexcept {
            return args.size();
        }
        
        constexpr std::string_view operator[](size_t i) const noexcept {
            return args[i];
        }
        
        constexpr auto begin() const noexcept {
            return args.begin();
        }
        
        constexpr auto end() const noexcept {
            return args.end();
        }
        
        constexpr std::string_view programName() const noexcept {
            return _programName;
        }
        
    };
    
}
