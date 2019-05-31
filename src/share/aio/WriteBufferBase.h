//
// Created by Khyber on 5/26/2019.
//

#pragma once

#include "src/share/aio/WriteBufferPool.h"

namespace aio {
    
    template <typename T, OnFatalError onFatalError, size_t N, typename... PoolTs>
    class WriteBufferBase {
    
    public:
        
        using Pool = WriteBufferPool<onFatalError, N, PoolTs...>;
        using Buffer = typename Pool::Buffer;
        
        static_assert(Pool::commonElementSize % sizeof(T) == 0, "sizeof(T) incompatible with Pools types");
        
        static constexpr size_t bufferSize = Pool::bufferSize / sizeof(T);
    
    private:
        
        const int fd;
        size_t offset = 0;
        
        Pool& pool;
        Buffer* _buffer = nullptr;
    
    public:
        
        WriteBufferBase(Pool& pool, int fd) noexcept : fd(fd), pool(pool) {
            _buffer = &pool.request();
        }
        
        ~WriteBufferBase() {
            close(fd);
        }
    
        deleteCopy(WriteBufferBase);
        
        constexpr size_t size() const noexcept {
            return _buffer->size();
        }
        
        T* raw() noexcept {
            return reinterpret_cast<T*>(_buffer->get());
        }
        
        // non-blocking
        template <bool finalWrite = false>
        void write(size_t n = bufferSize) noexcept(finalWrite) {
            if (n == 0) {
                return;
            }
            auto& buffer = *_buffer;
            auto& cb = buffer.cb;
            cb.fd() = fd;
            cb.offset() = offset * sizeof(T);
            buffer.setBuffer();
            cb.size() = n * sizeof(T);
            cb.signalMethod() = {.sigev_notify = SIGEV_NONE};
            if (cb.write() == -1) {
                // calling onFatalError signifies that this error/signal shouldn't be handled
                // if, for example, a runtime tries to flush after this fatal error,
                // then we might go into a signal loop
                onFatalError(std::error_code(errno, std::system_category()));
                abort();
            }
            offset += n;
            // if it's the finalWrite, we don't need to request another buffer,
            // which could throw on allocation, so it's noexcept in this case
            // this is important b/c write<finalWrite = true>
            // may be run in a signal handler caused by an allocation error
            // and this will ensure there are no exception/signal loops
            if constexpr (finalWrite) {
                _buffer = nullptr;
            } else {
                _buffer = &pool.request();
            }
        }
        
    };
    
}
