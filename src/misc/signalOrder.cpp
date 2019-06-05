//
// Created by Khyber on 6/5/2019.
//

#include <string_view>
#include <string>
#include <thread>
#include <iostream>

#include <csignal>

#include <unistd.h>
#include <sys/syscall.h>

void log(std::string_view sv) noexcept {
    write(STDERR_FILENO, sv.data(), sv.size());
}

/**
 * Test if the order I raise signals is always the order I receive them,
 * i.e. if I send a signal and then raise SIGKILL afterward,
 * the original signal should be received first.
 *
 * Answer: True, but I need to unblock the signal first inside of the signal handler.
 *      This can easily be done by using SA_RESETHAND, which unregisters the signal handler,
 *      and SA_NODEFER, which doesn't block the signal in it's own signal handler.
 */
int main() {
    const int signal = SIGILL;
    const struct sigaction action = {
            .sa_flags = static_cast<int>(SA_SIGINFO | SA_RESETHAND | SA_NODEFER),
            .sa_mask = {},
            .sa_sigaction = [](int signal, siginfo_t* info, void*) {
                log("received signal\n");
//                const struct sigaction noAction = {
//                        .sa_flags = 0,
//                        .sa_mask = {},
//                        .sa_handler = SIG_DFL,
//                };
//                sigaction(signal, &noAction, nullptr);
//                log("removed signal handler\n");
//                sigset_t mask = {};
//                sigaddset(&mask, signal);
//                sigprocmask(SIG_UNBLOCK, &mask, nullptr);
//                log("unblocked signal\n");
//                raise(signal);
                log("re-raised signal\n");
                syscall(SYS_rt_tgsigqueueinfo, getpid(), syscall(SYS_gettid), signal, info);
                
//                using namespace std::literals;
//                const auto now = []() {return std::chrono::steady_clock::now();};
//
//                const auto start = now();
//                while ((now() - start) < 100ms) {
//                    std::cerr << (now() - start).count() << std::endl;
//                }
//                std::this_thread::sleep_for(1000ms);
                raise(SIGKILL);
            },
    };
    sigaction(signal, &action, nullptr);
    raise(signal);
//    log("re-raised signal\n");
//    for (size_t i = 0;; i++) {
//        log(std::to_string(i) + "\n");
//        raise(signal);
//    }
}
