//
// Created by Khyber on 6/4/2019.
//

#include "src/share/capability/reboot.h"

#include "src/share/capability/Capabilities.h"

#include <cerrno>
#include <cassert>

namespace capability {
    
    bool reboot() noexcept {
        Capabilities capabilities {Header()};
        if (capabilities.get()) {
            return capabilities.effective().sysBoot;
        } else {
            assert(errno == EINVAL);
            errno = 0;
            return geteuid() == 0;
        }
    }
    
}
