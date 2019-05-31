//
// Created by Khyber on 4/7/2019.
//

#pragma once

#include "src/share/io/fs.h"

#include <string>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace fse {
    
    class Dir {
    
    private:
        
        const int fd;
    
    public:
        
        explicit constexpr Dir(int fd = AT_FDCWD) noexcept : fd(fd) {}
        
        explicit Dir(const fs::path& path);
        
        constexpr Dir(Dir&& other) noexcept : fd(other.fd) {
            const_cast<int&>(other.fd) = -1;
        }
    
        deleteCopy(Dir);
        
        ~Dir();
        
        Dir dir(const std::string& dirName, mode_t mode = 0755) const;
        
        int fileUnchecked(const std::string& fileName, int flags, mode_t mode = 0644) const;
        
        int file(const std::string& fileName, int flags, mode_t mode = 0644) const;
        
    };
    
}
