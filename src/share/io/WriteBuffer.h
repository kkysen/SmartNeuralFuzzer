//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include "src/share/common/math.h"
#include "src/share/io/fse.h"
#include "src/share/io/Writer.h"

namespace io {
    
    template <typename T>
    class WriteBuffer {
    
    private:
        
        static constexpr size_t pageSize = fse::page::constSize;
        
        static constexpr size_t bufferByteSize = math::lcm(pageSize, sizeof(T));
        static constexpr size_t bufferSize = bufferByteSize / sizeof(T);
        
        std::array<T, bufferSize> buffer = {};
        size_t index = 0;
        
        const Writer write;
        
        void writeBuffer(size_t numBytes = sizeof(buffer)) noexcept {
            write(buffer.begin(), numBytes);
        }
        
        void flush() noexcept {
            writeBuffer();
            index = 0;
        }
        
        constexpr bool shouldFlush() noexcept {
            return index == buffer.size();
        }
        
        void tryFlush() noexcept {
            if (shouldFlush()) {
                flush();
            }
        }
        
        void finalFlush() noexcept {
            writeBuffer(index * sizeof(T));
        }
    
    public:
        
        explicit constexpr WriteBuffer(Writer&& write) noexcept : write(std::move(write)) {}
        
        ~WriteBuffer() {
            finalFlush();
        }
        
        WriteBuffer(const WriteBuffer& other) = delete;
        
        void on(T t) noexcept {
            buffer[index++] = t;
            tryFlush();
        }
        
    };
    
}