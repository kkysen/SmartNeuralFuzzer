//
// Created by Khyber on 3/18/2019.
//

#pragma once

#include "src/share/io/fs.h"
#include "src/share/common/numbers.h"

#include <cstddef>
#include <cstring>

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

namespace fse {
    
    namespace page {
        
        constexpr size_t constSize = 4096; // only usually correct, but sometimes I need it as a constexpr
        const size_t dynamicSize = static_cast<const size_t>(sysconf(_SC_PAGESIZE));
        
    }
    
    fs::filesystem_error error(const std::string& what);
    
    fs::filesystem_error error(const std::string& what, const fs::path& path1);
    
    fs::filesystem_error error(const std::string& what, const fs::path& path1, const fs::path& path2);
    
    void* mmapRaw(int fd, int protection, int flags, size_t length, size_t offset = 0);
    
    template <typename T = u8>
    T* mmap(int fd, int protection, int flags, size_t length, size_t offset = 0) {
        return static_cast<T*>(mmapRaw(fd, protection, flags, length, offset));
    }
    
}
