//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include <unistd.h>

namespace io {
    
    class Write {
    
    public:
        
        int fd;
        
        constexpr bool isValid() noexcept {
            return fd >= 0;
        }
        
        explicit constexpr Write(int fd) : fd(fd) {}
        
        constexpr Write(Write&& other) noexcept : Write(other.fd) {
            other.fd = -1; // don't close(fd) early
        }
        
        Write(const Write& other) = delete;
        
        ~Write() noexcept;
        
        void operator()(const void* bytes, size_t numBytes) const noexcept;
        
        void absolute(const void* bytes, size_t numBytes, size_t offset = 0) const noexcept;
        
    };
    
}
