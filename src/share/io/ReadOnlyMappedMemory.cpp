//
// Created by Khyber on 5/21/2019.
//

#include "src/share/io/ReadOnlyMappedMemory.h"

#include "src/share/io/fse.h"
#include "src/share/io/Stat.h"

#include <sys/mman.h>

namespace io {
    
    ReadOnlyMappedMemory::ReadOnlyMappedMemory(bool close, int fd, size_t length, int flags)
            : _view(fse::mmap<const char>(fd, PROT_READ, flags, length), length) {
        if (close) {
            ::close(fd);
        }
    }
    
    ReadOnlyMappedMemory::ReadOnlyMappedMemory(bool close, int fd, int flags)
            : ReadOnlyMappedMemory(close, fd, Stat::fd(fd).checked().size(), flags) {}
    
    ReadOnlyMappedMemory::ReadOnlyMappedMemory(int fd, size_t length, int flags)
            : ReadOnlyMappedMemory(false, fd, length, flags) {}
    
    ReadOnlyMappedMemory::ReadOnlyMappedMemory(int fd, int flags)
            : ReadOnlyMappedMemory(false, fd, flags) {}
    
    ReadOnlyMappedMemory::ReadOnlyMappedMemory(const char* path, size_t length, int flags)
            : ReadOnlyMappedMemory(true, ::open(path, O_RDONLY), length, flags) {}
    
    ReadOnlyMappedMemory::ReadOnlyMappedMemory(const char* path, int flags)
            : ReadOnlyMappedMemory(true, ::open(path, O_RDONLY), flags) {}
    
    ReadOnlyMappedMemory::~ReadOnlyMappedMemory() {
        const void* data = _view.data();
        const size_t size = _view.size();
        if (data == MAP_FAILED || size == 0) {
            return;
        }
        ::munmap(const_cast<void*>(data), size);
    }
    
}
