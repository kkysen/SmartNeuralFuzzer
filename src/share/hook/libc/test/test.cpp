//
// Created by Khyber on 5/30/2019.
//

#include "src/share/hook/libc/syscall/gettid.h"

#include <cstdlib>
#include <csignal>
#include <cstdio>

#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

void printTid(bool parent) {
    printf("tid: %d (%s)\n", syscalls::gettid(), parent ? "parent" : "child");
}

int main() {
    if (!fork()) {
        _exit(0);
    }
    if (!fork()) {
        exit(0);
    }
    signal(SIGUSR1, nullptr);
    sigaction(SIGUSR2, nullptr, nullptr);
    if (!vfork()) {
        execlp("/bin/pwd", "pwd", nullptr);
    }
    
    pthread_t thread;
    pthread_attr_t attr = {};
    pthread_create(&thread, &attr, [](void* arg) {
        printTid(false);
        return arg;
    }, nullptr);
    printTid(true);
    void* exitVal = nullptr;
    pthread_join(thread, &exitVal);
    
    clone([](void*) { return 0; }, nullptr, 0, nullptr);
    
    std::quick_exit(0);
//    std::exit(0);
}
