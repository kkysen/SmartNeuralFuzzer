//
// Created by Khyber on 5/20/2019.
//

#pragma once

#include <src/share/io/Stat.h>
#include "src/share/io/fs.h"

#include "llvm/IR/Function.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSet.h"

#include <unordered_set>

namespace llvm::pass {
    
    /**
     * Given a set of binaries, filters out any function that is in one of the binaries.
     *
     * This is used in my coverage passes,
     * because I can't instrument any function that is part of the runtime.
     */
    class BinaryFunctionFilter {

    public:
        
        using StringRef = std::string_view;
        
        template <class T = StringRef>
        using StringSet = std::unordered_set<T>;

    private:
        
        SmallVector<StringRef, 1> mappedCacheFiles;
        
        StringSet<> functionNames;
    
    public:
        
        bool contains(StringRef functionName) const noexcept;
        
        bool operator()(StringRef functionName) const noexcept;
        
//        bool contains(Function& function) const noexcept;
        
//        bool operator()(Function& function) const noexcept;
        
        void add(StringRef functionName);
    
    private:
        
        void addMappedCacheFile(StringRef mappedCacheFile);
    
    public:
        
        void add(const fs::path& objectFilePath);
        
        ~BinaryFunctionFilter();
        
    };
    
}
