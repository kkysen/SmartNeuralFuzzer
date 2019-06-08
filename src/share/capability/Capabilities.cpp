//
// Created by Khyber on 6/4/2019.
//

#include "src/share/capability/Capabilities.h"

#include "src/share/common/hardAssert.h"

namespace capability {
    
    bool Capabilities::get() noexcept {
        return header.get(&data.impl());
    }
    
    bool Capabilities::set() const noexcept {
        return header.set(&data.impl());
    }
    
    Capabilities Capabilities::get(Header header) noexcept {
        Capabilities capabilities(header);
        hardAssert(capabilities.get());
        return capabilities;
    }
    
}
