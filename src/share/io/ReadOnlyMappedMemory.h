//
// Created by Khyber on 5/21/2019.
//

#pragma once

#include "src/share/io/fse.h"
#include "src/share/io/Stat.h"
#include "src/share/lib/corrade/CorradeArrayView.h"

#include <string_view>
#include <atomic>

#include <sys/mman.h>

namespace io {
    
    using namespace Corrade::Containers;
    
    template <typename T = u8>
    class ReadOnlyMappedMemory {
    
    public:
        
        using View = ArrayView<const T>;
        
        static constexpr int defaultFlags = MAP_PRIVATE;
    
    private:
        
        View _view;
        std::atomic<bool> moved = false;
    
    public:
        
        constexpr View view() const noexcept {
            return _view;
        }
    
    private:
        
        ReadOnlyMappedMemory(bool close, int fd, size_t length, int flags)
                : _view(fse::mmap<const T>(fd, PROT_READ, flags, length), length) {
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
            if (moved || _view.data() == static_cast<const T*>(MAP_FAILED) || _view.size() == 0) {
                return;
            }
            ::munmap(const_cast<T*>(_view.data()), _view.size());
        }
        
        deleteCopy(ReadOnlyMappedMemory);
        
        constexpr ReadOnlyMappedMemory(ReadOnlyMappedMemory&& other) noexcept
                : _view(other._view), moved(other.moved.exchange(true)) {}
        
    };
    
}
