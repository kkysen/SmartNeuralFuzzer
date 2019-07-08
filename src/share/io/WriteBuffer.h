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
        
        static constexpr size_t pageSize = fse::page::size::io::constant;
        
        static constexpr size_t bufferByteSize = math::lcm(pageSize, sizeof(T));
        static constexpr size_t bufferSize = bufferByteSize / sizeof(T);
        
        std::array<T, bufferSize> buffer = {};
        size_t index = 0;

    public:
        
        static constexpr size_t size() noexcept {
            return bufferSize;
        }
        
        constexpr size_t currentIndex() const noexcept {
            return index;
        }

    private:
        
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
        
        deleteCopy(WriteBuffer);
        
        void on(const T& t) noexcept {
            buffer[index++] = t;
            tryFlush();
        }
        
        WriteBuffer& operator<<(const T& t) noexcept {
            on(t);
            return *this;
        }
        
    };
    
}
