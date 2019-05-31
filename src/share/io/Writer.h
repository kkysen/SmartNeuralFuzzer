//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include "src/share/common/deleteCopy.h"

#include <unistd.h>

namespace io {
    
    class Writer {
    
    public:
        
        int fd;
        
        constexpr bool isValid() noexcept {
            return fd >= 0;
        }
        
        explicit constexpr Writer(int fd) : fd(fd) {}
        
        constexpr Writer(Writer&& other) noexcept : Writer(other.fd) {
            other.fd = -1; // don't close(fd) early
        }
        
        deleteCopy(Writer);
        
        ~Writer() noexcept;
        
        void operator()(const void* bytes, size_t numBytes) const noexcept;
        
        void absolute(const void* bytes, size_t numBytes, size_t offset = 0) const noexcept;
        
    };
    
}
