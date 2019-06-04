//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/Version.h"

#include <unistd.h>

namespace capability {
    
    class Header {

    public:
        
        // I'm only supporting Version 3
        const Version version = Version::v3;
        pid_t pid;
        
        using Impl = __user_cap_header_struct;
        
        /*implicit*/ constexpr Header(const Impl& impl) noexcept
                : version(static_cast<Version>(impl.version)), pid(impl.pid) {}
        
        const Impl& impl() const noexcept;
        
        Impl& impl() noexcept;
        
        /*implicit*/ operator const Impl&() const noexcept;
        
        /*implicit*/ operator Impl&() noexcept;
        
        explicit constexpr Header(pid_t pid) noexcept : pid(pid) {}
        
        Header() noexcept;

    private:
        
        Impl& mut() const noexcept;

    public:
        
        bool get(__user_cap_data_struct* data) const noexcept;
        
        bool set(const __user_cap_data_struct* data) const noexcept;
        
    };
    
}
