//
// Created by Khyber on 4/12/2019.
//

#pragma once

#include <llvm/ADT/ArrayRef.h>

#include <string_view>

using llvm::ArrayRef;

class Program {

public:
    
    using Args = ArrayRef<std::string_view>;
    
    const std::string_view name;
    const Args& args;
    
    constexpr Program(std::string_view name, const Args& args) noexcept : name(name), args(args) {}
    
    [[noreturn]] void exec();
    
    int awaitOrCatchForkExec();
    
    void awaitForkExec();
    
};

