//
// Created by Khyber on 2/17/2019.
//

#include <unistd.h>
#include <cstdio>

int main() {
    FILE* in = fopen("/mnt/c/Users/Khyber/workspace/misc/main.ll", "r");
    FILE* out = fopen("transformed.ll", "w");
    dup2(fileno(in), fileno(stdin));
    dup2(fileno(out), fileno(stdout));
    fclose(in);
    fclose(out);
    const char *opt = "/mnt/c/Users/Khyber/workspace/C++/llvm/build/bin/opt";
    execl(opt, opt, "-load", "./libBranchCoverage.so", "-branch-coverage", "-S", (char *) NULL);
    perror("");
    fprintf(stderr, "failed\n");
}
