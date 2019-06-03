//
// Created by Khyber on 6/2/2019.
//

#include <string_view>

#include <csignal>

#include <unistd.h>

void addHandler(int signal, void(* handler)(int)) noexcept {
    struct sigaction action = {
            .sa_flags = 0,
            .sa_mask = {},
            .sa_handler = handler,
    };
    ::sigaction(signal, &action, nullptr);
}

void removeHandler(int signal) noexcept {
    ::signal(signal, SIG_DFL);
}

void log(std::string_view sv) noexcept {
    write(STDERR_FILENO, sv.data(), sv.size());
}

/**
 * Test if a signal handler running inside of another signal handler exits to the first signal handler.
 *
 * Answer: true
 */
int main() {
    log("main start\n");
    const int signal = SIGUSR1;
    addHandler(signal, [](int signal) {
        log("outer start\n");
        addHandler(signal, [](int) {
            log("inner start\n");
            log("inner end\n");
        });
        sigset_t mask = {};
        sigemptyset(&mask);
        sigaddset(&mask, signal);
        ::sigprocmask(SIG_UNBLOCK, &mask, nullptr);
        raise(signal);
        log("outer end\n");
    });
    raise(signal);
    log("main end\n");
}
