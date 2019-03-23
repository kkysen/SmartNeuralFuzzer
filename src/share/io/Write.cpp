//
// Created by Khyber on 3/22/2019.
//

#include "src/share/io/Write.h"

Write::~Write() noexcept {
    if (isValid()) {
        close(fd);
    }
}

void Write::operator()(const void* bytes, size_t numBytes) const noexcept {
    ::write(fd, bytes, numBytes);
}

void Write::absolute(const void* bytes, size_t numBytes, size_t offset) const noexcept {
    ::pwrite(fd, bytes, numBytes, offset);
}
