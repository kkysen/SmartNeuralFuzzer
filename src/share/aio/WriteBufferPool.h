//
// Created by Khyber on 4/3/2019.
//

#pragma once

#include "src/share/aio/ControlBlock.h"
#include "src/share/common/math.h"
#include "src/share/io/fse.h"

#include "llvm/ADT/SmallVector.h"

namespace aio {
    
    template <size_t N, typename... Ts>
    class WriteBufferPool {
    
    public:
        
        static constexpr size_t commonElementSize = math::lcmSizeOf<Ts...>();
        static constexpr size_t bufferSize = fse::bufferSize(commonElementSize);

    private:
        
        using RawBuffer = std::array<u8, bufferSize>;
        
        class Buffer {

        private:
            
            RawBuffer buffer;

        public:
    
            constexpr size_t size() const noexcept {
                return buffer.size();
            }
    
            constexpr u8* get() noexcept {
                return buffer.data();
            }
            
            aio::ControlBlock cb;
            
            constexpr void resetAIO() noexcept {
                cb = {};
            }
            
            constexpr Buffer() noexcept : cb({}) {}
            
            constexpr void setBuffer() noexcept {
                cb.buffer() = buffer.data();
            }
            
        };
        
        llvm::SmallVector<Buffer, N> buffers; // buffer pool, buffers never moved
        llvm::SmallVector<Buffer*, N> pointers; // pointer to buffers pool, pointers moved
        
        Buffer& request() {
            // place all finished buffer pointers at end
            const auto next = std::partition(pointers.begin(), pointers.end(),
                                             [](const auto& buffer) { return !buffer->cb.finished(); });
            if (next != pointers.end()) {
                std::for_each(next, pointers.end(), [](const auto& buffer) { buffer->resetAIO(); });
                auto& buffer = **next;
                buffer.resetIndex();
                return buffer;
            } else {
                const auto nextIndex = buffers.size();
                buffers.emplace_back({});
                auto& buffer = buffers[nextIndex];
                pointers.emplace_back(&buffer);
                return buffer;
            }
        }
    
    public:
        
        WriteBufferPool() noexcept = default;
        
    };
    
    template <typename T, size_t N, typename... PoolTs>
    class WriteBufferBase {

    public:
        
        using Pool = WriteBufferPool<N, PoolTs...>;
        using Buffer = typename Pool::Buffer;
    
        // compatible type size
        static_assert(Pool::commonElementSize % sizeof(T) == 0);
        
        static constexpr size_t bufferSize = Pool::bufferSize / sizeof(T);
        
    private:
    
        const int fd;
        size_t offset = 0;
    
        Pool& pool;
        Buffer* buffer = nullptr;
        
    public:
        
        WriteBufferBase(Pool& pool, int fd) noexcept : fd(fd), pool(pool) {
            buffer = pool.request();
        }
    
        ~WriteBufferBase() {
            close(fd);
        }
        
        constexpr size_t size() const noexcept {
            return buffer->size();
        }
        
        T* raw() noexcept {
            return reinterpret_cast<T*>(buffer->get());
        }
    
        void write(size_t n = bufferSize) noexcept {
            if (n == 0) {
                return;
            }
            auto& buffer = *this->buffer;
            auto& cb = buffer.cb;
            cb.fd() = fd;
            cb.offset() = offset * sizeof(T);
            buffer.setBuffer();
            cb.size() = n * sizeof(T);
            cb.signalMethod() = SIGEV_NONE;
            assert(cb.write() != -1);
            offset += n;
            buffer = pool.request();
        }
        
    };
    
    template <typename T, size_t N, typename... PoolTs>
    class StandardWriteBuffer {

    public:
        
        using Buffer = WriteBufferBase<T, N, PoolTs...>;
        
    private:
        
        Buffer buffer;
        size_t index = 0;

    public:
        
        StandardWriteBuffer(typename Buffer::Pool& pool, int fd) : buffer(pool, fd) {}
        
        void write(size_t n = Buffer::bufferSize) noexcept {
            buffer.write(n);
        }
        
        void on(const T& t) noexcept {
            buffer.raw()[index++] = t;
            if (index == buffer.size()) {
                buffer.write();
                index = 0;
            }
        }
        
    };
    
    // other specializations can be made by composition,
    // like the boolean WriteBuffer for single branches
    
};