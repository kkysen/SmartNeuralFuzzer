//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include "src/share/capability/Header.h"
#include "src/share/capability/Data.h"

namespace capability {
    
    class Capabilities {
        
        const Header header;
        Data data;
    
    public:
        
        explicit Capabilities(Header header) noexcept : header(header), data({}) {}
        
        #define field(name) \
        \
        constexpr const Capability& name() const noexcept { \
            return data.name; \
        } \
        \
        constexpr Capability& name() noexcept { \
            return data.name; \
        }
        
        field(effective)
        
        field(permitted)
        
        field(inheritable)
        
        bool get() noexcept;
        
        bool set() const noexcept;
        
        static Capabilities get(Header header) noexcept;
        
    };
    
}
