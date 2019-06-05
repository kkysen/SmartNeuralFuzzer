//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/include.h"

#include "src/share/capability/reboot.h"
#include "src/share/common/numbers.h"

#include <cstdio>

extern "C"
int reboot(int cmd) noexcept {
    trace();
    bool shouldKill = false;
    switch (static_cast<u32>(cmd)) {
        case RB_AUTOBOOT:
        case RB_HALT_SYSTEM:
        case RB_POWER_OFF:
        case RB_SW_SUSPEND:
        case RB_KEXEC: {
            if (capability::reboot()) {
                shouldKill = true;
            }
        }
    }
    if (shouldKill) {
        onKill();
    }
    const auto retVal = impl::reboot(cmd);
    if (shouldKill) {
        perror("Correct reboot() call did not work, but we already shut down some stuff");
        impl::raise(SIGKILL);
    }
    return retVal;
}
