//
// Created by Khyber on 6/4/2019.
//

#include <iostream>

#include <sys/prctl.h>

/**
 * Test if prctl returns -errno or -1 and sets errno,
 * especially for the CAPBSET_READ and other capability flags.
 *
 * A libcap implementation thinks it returns -errno,
 * but I though glibc syscall wrappers and syscall() all return -1 and set errno.
 * Only the raw syscall is suppose to return -errno.
 *
 * Answer: prctl returns -1 and sets errno.
 */
int main() {
    std::cout << prctl(PR_CAPBSET_READ, -1) << std::endl;
    perror("");
}
