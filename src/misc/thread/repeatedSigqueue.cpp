//
// Created by Khyber on 6/3/2019.
//

#include <thread>
#include <atomic>
#include <iostream>
#include <sstream>

#include <csignal>

#include <unistd.h>
#include <vector>

std::atomic<size_t> count = 0;

void log(std::string_view sv) noexcept {
    write(STDERR_FILENO, sv.data(), sv.size());
}

thread_local size_t id;

/**
 * Test if multiple threads can be killed by by repeatedly raising a signal,
 * because in a signal handler, the signal is blocked from being received again,
 * but it doesn't work, because the same thread keeps receiving the signal.
 *
 * To do this correctly, I have to keep a list of pthread_t's or pid_t tid's.
 *
 * Answer: false
 */
int main() {
    using namespace std::literals;
    log("start: "s + std::to_string(count) + "\n"s);
    
    size_t n = 100;
    std::vector<std::thread> threads;
    for (size_t i = 0; i < n; i++) {
        threads.emplace_back([]() {
            ::id = ++count;
            for (;;) {
                log(std::to_string(::id) + "\n"s);
                ::sleep(1);
            }
        });
    }
    
    const int signal = SIGUSR2;
    
    const struct sigaction action = {
            .sa_flags = 0,
            .sa_mask = {},
            .sa_handler = [](int) {
                log("caught in "s + std::to_string(::id) + "\n"s);
                pause();
            },
    };
    ::sigaction(signal, &action, nullptr);
    
    sleep(2);
    for (size_t i = 0; i < n; i++) {
//        raise(signal);
        pthread_kill(threads[i].native_handle(), signal);
    }
    pthread_kill(pthread_self(), signal);
}
