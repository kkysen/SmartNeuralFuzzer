//
// Created by Khyber on 6/2/2019.
//

#include "src/share/hook/libc/syscall/getpid.h"
#include "src/share/hook/libc/syscall/getuid.h"

#include <string_view>

#include <csignal>

#include <unistd.h>
#include <syscall.h>

void log(std::string_view sv) noexcept {
    write(STDERR_FILENO, sv.data(), sv.size());
}

/**
 * Test what siginfo_t the syscall rt_sigqueueinfo (and the related rt_tgsigqueueinfo)
 * allow us to send beyond the fields listed in http://man7.org/linux/man-pages/man2/rt_sigqueueinfo.2.html.
 */
int main() {
    const int signal = SIGSEGV;
    
    struct sigaction action = {
            .sa_flags = SA_SIGINFO,
            .sa_mask = {},
            .sa_sigaction = [](int, siginfo_t* info, void*) {
                switch (info->si_signo) {
                    case SIGUSR1: {
                        log("SIGUSR1\n");
                        log(info->si_ptr == reinterpret_cast<void*>(0xCAFEBABE) ? "true" : "false");
                        log("\n");
                        break;
                    }
                    case SIGSEGV: {
                        log("SIGSEGV\n");
                        log(info->si_addr == reinterpret_cast<void*>(0xCAFEBABE) ? "true" : "false");
                        log("\n");
                        break;
                    }
                }
            },
    };
    ::sigaction(signal, &action, nullptr);
    
    siginfo_t info = {};
    info.si_signo = signal;
    info.si_code = -1;
    
    switch (info.si_signo) {
        case SIGUSR1: {
            info.si_pid = getpid();
            info.si_uid = getuid();
            info.si_value = sigval_t {
                    .sival_ptr = reinterpret_cast<void*>(0xCAFEBABE),
            };
            break;
        }
        case SIGSEGV: {
            info.si_addr = reinterpret_cast<void*>(0xCAFEBABE);
            break;
        }
    }
    
    ::syscall(SYS_rt_sigqueueinfo, getpid(), signal, &info);
}
