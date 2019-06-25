//
// Created by Khyber on 5/20/2019.
//

#pragma once

#include "src/share/io/ReadOnlyMappedMemory.h"
#include "src/share/common/lazy.h"

#include "llvm/IR/Function.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSet.h"

namespace llvm::pass {
    
    /**
     * Given a set of binaries, filters out any function that is in one of the binaries.
     *
     * This is used in my coverage passes,
     * because I can't instrument any function that is part of the runtime.
     */
    class BinaryFunctionFilter {
    
    private:
        
        // will be used by 2 runtime files
        SmallVector<io::ReadOnlyMappedMemory<char>, 2> mappedCacheFiles;
        
        StringSet<> functionNames;
    
    public:
        
        bool contains(StringRef functionName) const noexcept;
        
        bool operator()(StringRef functionName) const noexcept;
    
        void add(StringRef functionName);
        
        
        
        bool contains(std::string_view functionName) const noexcept;
        
        bool operator()(std::string_view functionName) const noexcept;
        
        void add(std::string_view functionName);
    
    private:
        
        void addMappedCacheFile(io::ReadOnlyMappedMemory<char>&& mappedCacheFile);
    
    public:
        
        void add(const fs::path& objectFilePath);

    private:
        
        // purge cache every time binary is loaded, so once every compilation
        // each compilation doesn't take long, and the expiration time is 24h
        static RunOnce<> purgeCache;
        
    };
    
}
