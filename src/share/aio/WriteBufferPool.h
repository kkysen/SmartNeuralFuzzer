//
// Created by Khyber on 4/3/2019.
//

#pragma once

#include "src/share/aio/ControlBlock.h"
#include "src/share/common/math.h"
#include "src/share/io/fse.h"

#include "llvm/ADT/SmallVector.h"

#include <functional>

namespace aio {
    
    using OnFatalError = void (*)(const std::error_code&);
    
    template <OnFatalError onFatalError, size_t N, typename... Ts>
    class WriteBufferPool {
    
    public:
        
        static constexpr size_t commonElementSize = math::lcmSizeOf<Ts...>();
        static constexpr size_t bufferSize = fse::bufferSize(commonElementSize);
        
        class Buffer {
        
        public:
            
            using Raw = std::array<u8, bufferSize>;
            
            // ControlBlock must be the first member
            // so that a Buffer* can be casted to a ControlBlock*
            ControlBlock cb = {};
        
        private:
            
            Raw buffer;
        
        public:
            
            constexpr size_t size() const noexcept {
                return buffer.size();
            }
            
            constexpr u8* get() noexcept {
                return buffer.data();
            }
            
            constexpr void resetAIO() noexcept {
                cb = {};
            }
            
            constexpr Buffer() noexcept = default;
            
            constexpr void setBuffer() noexcept {
                cb.buffer() = buffer.data();
            }
            
        };
    
    private:
        
        template <typename T>
        using SmallVector = llvm::SmallVector<T, N>;
        
        SmallVector<Buffer> buffers; // buffer pool, buffers never moved
        SmallVector<Buffer*> pointers; // pointer to buffers pool, pointers moved
    
    public:
        
        constexpr size_t size() const noexcept {
            return pointers.size();
        }
        
        // doesn't allocate, so noexcept
        // returns nullptr if it can't find a buffer w/o allocating a new one
        Buffer* requestExisting() noexcept {
            // place all finished buffer pointers at end
            const auto next = std::partition(pointers.begin(), pointers.end(),
                                             [](const Buffer* buffer) { return !buffer->cb.idle(); });
            if (next == pointers.end()) {
                return nullptr;
            }
            // reset all finished buffers
            std::for_each(next, pointers.end(), std::mem_fn(&Buffer::resetAIO));
            return *next;
        }
        
        // non-blocking, rarely will allocate
        // faster to allocate instead of blocking on aio_suspend()
        Buffer& request() noexcept(false) {
            auto* bufferPtr = requestExisting();
            if (bufferPtr) {
                return *bufferPtr;
            }
            const auto nextIndex = buffers.size();
            buffers.emplace_back();
            auto& buffer = buffers[nextIndex];
            pointers.emplace_back(&buffer);
            return buffer;
        }
    
    private:
        
        Buffer* requestAwait(const TimeSpec* timeout, int& error) noexcept {
            auto* bufferPtr = requestExisting();
            if (bufferPtr) {
                return bufferPtr;
            }
            // SmallVector<Buffer*> -> ArrayRef<Buffer*> -> ArrayRef<ControlBlock*> -> ControlBlock** -> aiocb**
            const auto controlBlocks = reinterpret_cast<const ControlBlock* const*>(pointers.data());
            const auto ref = llvm::ArrayRef(controlBlocks, size());
            if (aio::suspend(ref, timeout) == -1) {
                error = errno;
            } else {
                error = 0;
            }
            return requestExisting();
        }
    
    public:
        
        // blocking (up to timeout), but never allocates, so noexcept
        Buffer* requestAwait(const TimeSpec& timeout, int& error) {
            return requestAwait(&timeout, error);
        }
        
        // blocking, but never allocates, so noexcept, but always finds a valid Buffer&
        // unless interrupted, then it still returns nullptr)
        // that's why I have to still return a pointer instead of a reference
        Buffer* requestAwait(int& error) noexcept {
            // with no timeout, requestAwait won't return until it has a valid Buffer*
            return requestAwait(nullptr, error);
        }
        
        Buffer& requestAwait() noexcept {
            int e;
            auto* bufferPtr = requestAwait(e);
            if (e) {
                onFatalError(std::error_code(e, std::system_category()));
                abort();
            }
            return *bufferPtr;
        }
        
        WriteBufferPool() = default;
    
        deleteCopy(WriteBufferPool);
    
    private:
        
        // this would be a templated lambda in C++20
        template <template <typename, OnFatalError, size_t, typename...> class WrappedBuffer, typename T>
        struct WrappedBufferConstructor {
            
            WriteBufferPool& pool;
            
            template <class... Args>
            auto operator()(Args&& ...args) {
                return WrappedBuffer<T, onFatalError, N, Ts...>(pool, std::move(args)...);
            }
            
        };
    
    public:
        
        template <template <typename, OnFatalError, size_t, typename...> class WrappedBuffer,
                typename T>
        auto request() {
            return WrappedBufferConstructor<WrappedBuffer, T> {*this};
        }
        
    };
    
};
