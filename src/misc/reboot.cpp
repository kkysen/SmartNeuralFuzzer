//
// Created by Khyber on 6/3/2019.
//

#include "src/share/capability/reboot.h"

#include <iostream>

#include <unistd.h>
#include <sys/reboot.h>

/**
 * Test if reboot really works when capability::reboot() is true.
 *
 * Answer: for RB_POWER_OFF in Ubuntu WSL, WSL shuts down.
 * But for RB_AUTOBOOT, the kernel returns EINVAL for some reason.
 */
int main() {
    std::cout << std::boolalpha;
    const bool canReboot = capability::reboot();
    std::cout << "canReboot: " << canReboot << std::endl;
    if (canReboot) {
        std::cout << "reboot?" << std::endl;
        sleep(3);
//        const int cmd = RB_AUTOBOOT;
        const int cmd = RB_POWER_OFF;
        std::cout << reboot(cmd) << std::endl;
        perror("");
    }
}
