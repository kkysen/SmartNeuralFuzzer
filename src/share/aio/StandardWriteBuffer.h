//
// Created by Khyber on 5/26/2019.
//

#pragma once

#include "src/share/aio/WriteBufferBase.h"

namespace aio {
    
    template <typename T, OnFatalError onFatalError, size_t N, typename... PoolTs>
    class StandardWriteBuffer {
    
    public:
        
        using Buffer = WriteBufferBase<T, onFatalError, N, PoolTs...>;
    
    private:
        
        Buffer buffer;
        size_t index = 0;
        
        template <bool finalWrite = false>
        void write() noexcept(finalWrite) {
            buffer.template write<finalWrite>(index);
        }
    
    public:
        
        constexpr size_t size() const noexcept {
            return buffer.size();
        }
        
        StandardWriteBuffer(typename Buffer::Pool& pool, int fd) : buffer(pool, fd) {}
        
        ~StandardWriteBuffer() {
            write<true>();
        }
        
        void on(const T& t) noexcept(false) {
            buffer.raw()[index++] = t;
            if (index == buffer.size()) {
                write();
                index = 0;
            }
        }
        
        StandardWriteBuffer& operator<<(const T& t) noexcept(false) {
            on(t);
            return *this;
        }
        
    };
    
    // other specializations can be made by composition,
    // like the boolean WriteBuffer for single branches
    
}
