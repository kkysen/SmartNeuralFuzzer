//
// Created by Khyber on 5/21/2019.
//

#pragma once

#include "src/share/io/fse.h"
#include "src/share/io/Stat.h"
#include "src/share/lib/corrade/CorradeArrayView.h"

#include <string_view>

#include <sys/mman.h>

namespace io {
    
    using namespace Corrade::Containers;
    
    template <typename T = u8>
    class ReadOnlyMappedMemory : public ArrayView<const T> {
    
    public:
        
        using Super = ArrayView<const T>;
        
        static constexpr int defaultFlags = MAP_PRIVATE;
        
        static constexpr auto failed = static_cast<const T*>(MAP_FAILED);
    
        using Super::data;
        using Super::size;
        
    private:
        
        ReadOnlyMappedMemory(bool close, int fd, size_t length, int flags)
                : Super(fse::mmap<const T>(fd, PROT_READ, flags, length), length) {
            if (close) {
                ::close(fd);
            }
        }
        
        ReadOnlyMappedMemory(bool close, int fd, int flags)
                : ReadOnlyMappedMemory(close, fd, Stat::fd(fd).checked().size(), flags) {}
    
    public:
        
        ReadOnlyMappedMemory(int fd, size_t length, int flags = defaultFlags)
                : ReadOnlyMappedMemory(false, fd, length, flags) {}
        
        explicit ReadOnlyMappedMemory(int fd, int flags = defaultFlags)
                : ReadOnlyMappedMemory(false, fd, flags) {}
        
        explicit ReadOnlyMappedMemory(const char* path, int flags = defaultFlags)
                : ReadOnlyMappedMemory(true, ::open(path, O_RDONLY), flags) {}
        
        ReadOnlyMappedMemory(const char* path, size_t length, int flags = defaultFlags)
                : ReadOnlyMappedMemory(true, ::open(path, O_RDONLY), length, flags) {}
        
        template <class String>
        explicit ReadOnlyMappedMemory(const String& path, int flags = defaultFlags)
                : ReadOnlyMappedMemory(path.c_str(), flags) {}
        
        template <class String>
        ReadOnlyMappedMemory(const String& path, size_t length, int flags = defaultFlags)
                : ReadOnlyMappedMemory(path.c_str(), length, flags) {}
        
        ~ReadOnlyMappedMemory() {
            if (data() == failed || size() == 0) {
                return;
            }
            ::munmap(const_cast<T*>(data()), size());
        }
        
        deleteCopy(ReadOnlyMappedMemory);
        
        constexpr ReadOnlyMappedMemory(ReadOnlyMappedMemory&& other) noexcept : Super(other) {
            other.data() = static_cast<const T*>(MAP_FAILED);
            other.size() = 0;
        }
        
    };
    
}
