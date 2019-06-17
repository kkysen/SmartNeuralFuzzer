//
// Created by Khyber on 6/17/2019.
//

#pragma once

#include "src/share/io/env/Environment.h"

namespace env {
    
    class Exec {
    
    private:
        
        static constexpr size_t argcEstimate = 5;
        
        const int fd = -1;
        const bool isPath = true;
        const char* const path = nullptr;
        llvm::SmallVector<const char*, argcEstimate + 1> _argv;
        
        static constexpr bool determineIfIsPath(const char* path) noexcept {
            return path[0] == '/' // absolute path
                   || (path[0] == '.' && path[1] == '/') // ./
                   || (path[0] == '.' && path[1] == '.' && path[2] == '/'); // ../
        }
    
    public:
        
        explicit Exec(int fd);
        
        template <typename... Args>
        explicit Exec(const char* path, Args... rest)
                : isPath(determineIfIsPath(path)), path(path), _argv({path, rest...}) {}
        
        constexpr const llvm::SmallVectorImpl<const char*>& argv() const noexcept {
            return _argv;
        }
        
        constexpr llvm::SmallVectorImpl<const char*>& argv() noexcept {
            return _argv;
        }
    
    private:
        
        void _print(std::ostream& out) const;
    
    public:
        
        const Exec& print(std::ostream& out) const;
        
        Exec& print(std::ostream& out);
    
    private:
        
        void ensureArgvNullTerminated() const;
        
        int execReturn(const Environment& env) const noexcept;
    
    public:
        
        void exec(const Environment& env = Environment()) const;
        
        void operator()(const Environment& env = Environment()) const;
        
    };
    
}
