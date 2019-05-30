//
// Created by Khyber on 4/3/2019.
//

#pragma once

#include "src/share/time/TimeSpec.h"

#include "llvm/ADT/ArrayRef.h"

#include <cerrno>
#include <aio.h>

namespace aio {
    
    using _time::TimeSpec;
    
    class ControlBlock {
    
    private:
        
        aiocb _cb;
        
        constexpr aiocb* ptr() const noexcept {
            return &const_cast<aiocb&>(_cb);
        }
    
    public:
        
        struct Args {
            
            int fd;
            off_t offset;
            volatile void* buffer;
            size_t size;
            int requestPriority;
            sigevent signalMethod;
            int listOperation;
            
            constexpr aiocb operator()() noexcept {
                return {
                        .aio_fildes = fd,
                        .aio_offset = offset,
                        .aio_buf = buffer,
                        .aio_nbytes = size,
                        .aio_reqprio = requestPriority,
                        .aio_sigevent = signalMethod,
                        .aio_lio_opcode = listOperation,
                };
            }
            
        };
        
        constexpr ControlBlock() noexcept : _cb({}) {}
        
        /*implicit*/ constexpr ControlBlock(Args args) noexcept : _cb(args()) {}
        
        /*implicit*/ operator aiocb() const noexcept {
            return _cb;
        }
        
        constexpr const aiocb& cb() const noexcept {
            return _cb;
        }
        
        constexpr aiocb& cb() noexcept {
            return _cb;
        }
        
        
        constexpr const int& fd() const noexcept {
            return _cb.aio_fildes;
        }
        
        constexpr int& fd() noexcept {
            return _cb.aio_fildes;
        }
        
        constexpr const off_t& offset() const noexcept {
            return _cb.aio_offset;
        }
        
        constexpr off_t& offset() noexcept {
            return _cb.aio_offset;
        }
        
        // can't make this return a reference for some reason
        constexpr const volatile void* buffer() const noexcept {
            return _cb.aio_buf;
        }
        
        constexpr volatile void*& buffer() noexcept {
            return _cb.aio_buf;
        }
        
        constexpr const size_t& size() const noexcept {
            return _cb.aio_nbytes;
        }
        
        constexpr size_t& size() noexcept {
            return _cb.aio_nbytes;
        }
        
        constexpr const int& requestPriority() const noexcept {
            return _cb.aio_reqprio;
        }
        
        constexpr int& requestPriority() noexcept {
            return _cb.aio_reqprio;
        }
        
        constexpr const sigevent& signalMethod() const noexcept {
            return _cb.aio_sigevent;
        }
        
        constexpr sigevent& signalMethod() noexcept {
            return _cb.aio_sigevent;
        }
        
        constexpr const int& listOperation() const noexcept {
            return _cb.aio_lio_opcode;
        }
        
        constexpr int& listOperation() noexcept {
            return _cb.aio_lio_opcode;
        }
        
        
        int read() const noexcept;
        
        int write() const noexcept;
        
        int fsync(int op) const noexcept;
        
        int error() const noexcept;
        
        ssize_t returnValue() const noexcept;
        
        int cancel() const noexcept;
        
        int suspend(const TimeSpec* = nullptr) const noexcept;
        
        int suspend(const TimeSpec& timeout) const noexcept;
        
        bool idle() const noexcept;
        
    };
    
    void init(const aioinit& init) noexcept;
    
    int read(const ControlBlock& cb) noexcept;
    
    int write(const ControlBlock& cb) noexcept;
    
    int fsync(const ControlBlock& cb, int op) noexcept;
    
    int error(const ControlBlock& cb) noexcept;
    
    ssize_t returnValue(const ControlBlock& cb) noexcept;
    
    int cancel(const ControlBlock& cb) noexcept;
    
    int suspend(llvm::ArrayRef<const ControlBlock*> cbs, const TimeSpec* timeout = nullptr) noexcept;
    
    int suspend(llvm::ArrayRef<const ControlBlock*> cbs, const TimeSpec& timeout) noexcept;
    
    int suspend(const ControlBlock& cb, const TimeSpec* timeout = nullptr) noexcept;
    
    int suspend(const ControlBlock& cb, const TimeSpec& timeout) noexcept;
    
    bool idle(const ControlBlock& cb) noexcept;
    
}
