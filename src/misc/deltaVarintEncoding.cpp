//
// Created by Khyber on 6/13/2019.
//

#include "src/share/io/Stat.h"

#include <iostream>

#include <fcntl.h>

u64 lastBlock = 0;
u64 totalBits = 0;

void process(const char* buffer, size_t n) {
    const u64* blocks = reinterpret_cast<const u64*>(buffer);
    const auto m = n / sizeof(u64);
    for (size_t i = 0; i < m; i++) {
        const auto block = blocks[i];
        const auto delta = math::difference(block, lastBlock);
//        std::cout << "delta: " << delta << std::endl;
        lastBlock = block;
        const auto bits = (sizeof(u64) * CHAR_BIT - __builtin_clzl(delta)) + 1 + 1; // 1 for sign bit
//        std::cout << "bits: " << bits << std::endl;
        totalBits += bits;
    }
//    sleep(1);
}

void print(const io::Stat& stats) {
    const auto size = stats.size();
    const auto optimizedSize = totalBits / CHAR_BIT;
    std::cout << optimizedSize << "/" << size << std::endl;
}

void run(int argc, char** argv) {
    if (argc < 2) {
        return;
    }
    const char* path = argv[1];
    const int fd = open(path, O_RDONLY);
    const auto stats = io::Stat::fd(fd);
    
    char buffer[stats.blockSize];
    ssize_t n;
//    size_t i = 0;
    do {
        n = read(fd, buffer, sizeof(buffer));
        if (n == -1) {
            std::cerr << "error" << std::endl;
            exit(1);
        }
        process(buffer, n);
//        if (i++ % 1000 == 0) {
//            std::cout << totalBits << std::endl;
//        }
    } while (n != 0);
    print(stats);
}

int main(int argc, char** argv) {
    run(argc, argv);
}
