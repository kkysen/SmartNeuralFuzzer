//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include "src/share/common/math.h"
#include "fse.h"
#include "Write.h"

template <typename T>
class Buffer {

private:
    
    static constexpr size_t pageSize = fse::page::constSize;
    
    static constexpr size_t bufferByteSize = math::lcm(pageSize, sizeof(T));
    static constexpr size_t bufferSize = bufferByteSize / sizeof(T);
    
    std::array<T, bufferSize> buffer = {};
    size_t index = 0;
    
    const Write write;
    
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
    
    explicit constexpr Buffer(Write&& write) noexcept : write(std::move(write)) {}
    
    ~Buffer() {
        finalFlush();
    }
    
    void on(T t) noexcept {
        buffer[index++] = t;
        tryFlush();
    }
    
};
