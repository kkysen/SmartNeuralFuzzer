//
// Created by Khyber on 4/6/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/aio/ControlBlock.h"

#include <array>
#include <unistd.h>

namespace aio {
    
    /**
     * Used for when writing T can be overwritten,
     * i.e. writing T is idempotent,
     * because it can be repeatedly written without making the written value of T incorrect.
     */
    class IdempotentWriter {
    
    private:
        
        const aio::ControlBlock cb;
    
    public:
        
        // non-blocking
        void write() const noexcept;
        
        constexpr IdempotentWriter(int fd, const void* buffer, size_t size) noexcept
                : cb({
                             .fd = fd,
                             .offset = 0,
                             .buffer = const_cast<volatile void*>(buffer),
                             .size = size,
                             .signalMethod = {.sigev_notify = SIGEV_NONE},
                     }) {}
        
        template <typename T>
        constexpr IdempotentWriter(int fd, const T& t) noexcept : IdempotentWriter(fd, &t, sizeof(t)) {}
        
        ~IdempotentWriter();
    
        deleteCopy(IdempotentWriter);
        
    };
    
}
