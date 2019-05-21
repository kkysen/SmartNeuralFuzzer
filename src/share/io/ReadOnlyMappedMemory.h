//
// Created by Khyber on 5/21/2019.
//

#pragma once

#include "src/share/io/fs.h"

#include <string_view>
#include <sys/mman.h>

namespace io {
    
    class ReadOnlyMappedMemory {
    
    private:
        
        std::string_view _view;
    
    public:
        
        constexpr std::string_view view() const noexcept {
            return _view;
        }
        
        static constexpr int defaultFlags = MAP_PRIVATE;

    private:

        ReadOnlyMappedMemory(bool close, int fd, size_t length, int flags);
    
        ReadOnlyMappedMemory(bool close, int fd, int flags);
    
    public:
    
        ReadOnlyMappedMemory(int fd, size_t length, int flags = defaultFlags);
        
        explicit ReadOnlyMappedMemory(int fd, int flags = defaultFlags);
        
        explicit ReadOnlyMappedMemory(const char* path, int flags = defaultFlags);
        
        template <class String>
        explicit ReadOnlyMappedMemory(const String& path, int flags = defaultFlags) : ReadOnlyMappedMemory(path.c_str(), flags) {}
        
        ReadOnlyMappedMemory(const char* path, size_t length, int flags = defaultFlags);
        
        template <class String>
        ReadOnlyMappedMemory(const String& path, size_t length, int flags = defaultFlags)
                : ReadOnlyMappedMemory(path.c_str(), length, flags) {}
        
        ~ReadOnlyMappedMemory();
        
        ReadOnlyMappedMemory(const ReadOnlyMappedMemory& other) = delete;
        
        constexpr ReadOnlyMappedMemory(ReadOnlyMappedMemory&& other) noexcept : _view(other._view) {
            other._view = std::string_view(static_cast<const char*>(MAP_FAILED), 0);
        }
        
    };
    
}
