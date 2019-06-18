//
// Created by Khyber on 6/17/2019.
//

#include "src/share/common/numbers.h"

#include <iostream>

#include <cstdlib>

#include <fcntl.h>
#include <unistd.h>

void run(const char* path) {
    const int fd = ::open(path, O_RDONLY);
    if (fd == -1) {
        exit(EXIT_FAILURE);
    }
    struct {
        u64 single;
        u64 multi;
        u64 infinite;
    } branches = {};
    ::read(fd, &branches, sizeof(branches));
    #define _(field) std::cout << ""#field": " << branches.field << std::endl
    _(single);
    _(multi);
    _(infinite);
}

int main(int, char** argv) {
    run(argv[1]);
}
