//
// Created by Khyber on 6/12/2019.
//

#pragma once

#include <vector>
#include <string>

#include "src/share/lib/corrade/CorradeArrayView.h"

namespace io {
    
    using namespace Corrade::Containers;
    
    class Argv {
        
        std::string raw;
        std::vector<std::string_view> args;
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
        
        constexpr std::string_view programName() const noexcept {
            return _programName;
        }
        
    };
    
}
