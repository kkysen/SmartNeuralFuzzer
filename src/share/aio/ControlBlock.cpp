//
// Created by Khyber on 4/3/2019.
//

#include "src/share/aio/ControlBlock.h"

namespace {
    
    using _time::TimeSpec;
    
    const timespec* cast(const TimeSpec* timeSpec) {
        // TimeSpec and timespec have the same memory layout, just different member names
        // so this reinterpret_cast is safe
        return reinterpret_cast<const timespec*>(timeSpec);
    }
    
}

namespace aio {
    
    int ControlBlock::read() const noexcept {
        return aio_read(ptr());
    }
    
    int ControlBlock::write() const noexcept {
        return aio_write(ptr());
    }
    
    int ControlBlock::fsync(int op) const noexcept {
        return aio_fsync(op, ptr());
    }
    
    int ControlBlock::error() const noexcept {
        return aio_error(ptr());
    }
    
    ssize_t ControlBlock::returnValue() const noexcept {
        return aio_return(ptr());
    }
    
    int ControlBlock::cancel() const noexcept {
        return aio_cancel(fd(), ptr());
    }
    
    int ControlBlock::suspend(const TimeSpec* timeout) const noexcept {
        return aio::suspend(*this, timeout);
    }
    
    int ControlBlock::suspend(const TimeSpec& timeout) const noexcept {
        return aio::suspend(*this, timeout);
    }
    
    bool ControlBlock::idle() const noexcept {
        const int e = error();
        // idle if 0 (completed), ECANCELED (cancelled), or EINVAL (no aio call made yet)
        return e == 0 || e == ECANCELED || e == EINVAL;
    }
    
    void init(const aioinit& init) noexcept {
        aio_init(&init);
    }
    
    int read(const ControlBlock& cb) noexcept {
        return cb.read();
    }
    
    int write(const ControlBlock& cb) noexcept {
        return cb.write();
    }
    
    int fsync(const ControlBlock& cb, int op) noexcept {
        return cb.fsync(op);
    }
    
    int error(const ControlBlock& cb) noexcept {
        return cb.error();
    }
    
    ssize_t returnValue(const ControlBlock& cb) noexcept {
        return cb.returnValue();
    }
    
    int cancel(const ControlBlock& cb) noexcept {
        return cb.cancel();
    }
    
    int suspend(llvm::ArrayRef<const ControlBlock*> cbs, const TimeSpec* timeout) noexcept {
        return aio_suspend(reinterpret_cast<const aiocb* const*>(cbs.data()),
                           static_cast<int>(cbs.size()), ::cast(timeout));
    }
    
    int suspend(llvm::ArrayRef<const ControlBlock*> cbs, const TimeSpec& timeout) noexcept {
        return suspend(cbs, &timeout);
    }
    
    int suspend(const ControlBlock& cb, const TimeSpec* timeout) noexcept {
        const aiocb* cbs = &cb.cb();
        return aio_suspend(&cbs, 1, ::cast(timeout));
    }
    
    int suspend(const ControlBlock& cb, const TimeSpec& timeout) noexcept {
        return suspend(cb, &timeout);
    }
    
    bool idle(const ControlBlock& cb) noexcept {
        return cb.idle();
    }
    
}
