//
// Created by Khyber on 5/26/2019.
//

#pragma once

#include "src/share/aio/WriteBufferBase.h"

namespace aio {
    
    template <typename T, OnFatalError onFatalError, size_t N, typename... PoolTs>
    class StandardWriteBuffer {
    
    public:
        
        using Buffer = aio::WriteBufferBase<T, onFatalError, N, PoolTs...>;
    
    private:
        
        Buffer buffer;
        size_t index = 0;
        
        template <bool finalWrite = false>
        void write() noexcept(finalWrite) {
            buffer.template write<finalWrite>(index);
        }
    
    public:
        
        StandardWriteBuffer(typename WriteBufferBase::Pool& pool, int fd) : buffer(pool, fd) {}
        
        ~StandardWriteBuffer() {
            write<true>();
        }
        
        void on(const T& t) noexcept {
            buffer.raw()[index++] = t;
            if (index == buffer.size()) {
                write();
                index = 0;
            }
        }
        
        void operator()(const T& t) noexcept {
            on(t);
        }
        
    };
    
    // other specializations can be made by composition,
    // like the boolean WriteBuffer for single branches
    
}

namespace test {
    
    // TODO FIXME remove this is just for compilation testing
    
    using namespace aio;
    
    bool fatal = false;
    
    void onFatalError(const std::error_code&) {
        fatal = true;
    }
    
    void f() {
        WriteBufferPool<onFatalError, 2, int, long> pool;
        int fd = 1;
        auto buffer = pool.request<StandardWriteBuffer, int>()(fd);
        buffer(1);
    }
    
}
