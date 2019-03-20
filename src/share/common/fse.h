//
// Created by Khyber on 3/18/2019.
//

#pragma once

// fs-extra
#include "src/share/common/numbers.h"
#include "debug.h"

#include <cstddef>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

namespace fse {
    
    const size_t pageSize = static_cast<const size_t>(sysconf(_SC_PAGESIZE));
    
    template <typename T = u8>
    T* mmap(int fd, int protection, int flags, size_t length, size_t offset = 0) {
        if (length == 0) {
            return nullptr;
        }
        void* memory = ::mmap(nullptr, length, protection, flags, fd, offset);
        if (memory == MAP_FAILED) {
            throw fs::filesystem_error("mmap failed for fd = " + std::to_string(fd), std::error_code());
        }
        _dbg("before write");
        static_cast<char*>(memory)[length - 1] = 'A';
        msync(memory, length, MS_ASYNC);
        std::cout << std::string_view(static_cast<char*>(memory), length) << std::endl;
        _dbg("after write");
        munmap(memory, length);
        return static_cast<T*>(memory);
    }
    
}
