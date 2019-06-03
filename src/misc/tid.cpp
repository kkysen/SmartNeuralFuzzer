//
// Created by Khyber on 6/3/2019.
//

#include <thread>
#include <vector>

#include <unistd.h>
#include <sys/syscall.h>

//const pid_t pid = getpid();

pid_t gettid() noexcept {
    return syscall(SYS_gettid);
}

pid_t tidDelta() noexcept {
    return gettid() - getpid();
}

void log(std::string_view sv) noexcept {
    write(STDERR_FILENO, sv.data(), sv.size());
}

int main() {
    const size_t n = 100;
    std::vector<std::thread> threads;
    for (;;) {
        for (size_t i = 0; i < n; i++) {
            threads.emplace_back([]() {
                log(std::to_string(tidDelta()) + "\n");
                sleep(5);
                pthread_exit(nullptr);
            });
        }
        sleep(1);
//        for (size_t i = 0; i < n; i += 2) {
//            threads.erase(threads.begin() + i);
//        }
    }
}
