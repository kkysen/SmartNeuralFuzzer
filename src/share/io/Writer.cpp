//
// Created by Khyber on 3/22/2019.
//

#include "src/share/io/Writer.h"

namespace io {
    
    Writer::~Writer() noexcept {
        if (isValid()) {
            close(fd);
        }
    }
    
    void Writer::operator()(const void* bytes, size_t numBytes) const noexcept {
        ::write(fd, bytes, numBytes);
    }
    
    void Writer::absolute(const void* bytes, size_t numBytes, size_t offset) const noexcept {
        ::pwrite(fd, bytes, numBytes, offset);
    }
    
}
