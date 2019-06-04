//
// Created by Khyber on 6/4/2019.
//

#include "src/share/capability/Version.h"

#include "src/share/hook/libc/syscall/cap.h"

#include <cerrno>
#include <cassert>

#include <unistd.h>

#include <cstdio>

namespace {
    
    using capability::Version;
    
    Version getPreferredVersion() noexcept {
        __user_cap_header_struct header = {
                .version = static_cast<u32>(-1),
                .pid = getpid(),
        };
        if (::capget(&header, nullptr) == -1) {
            assert(errno == EINVAL);
            errno = 0;
        }
        return static_cast<Version>(header.version);
    }
    
}

namespace capability {
    
    const Version preferredVersion = getPreferredVersion();
    
}
