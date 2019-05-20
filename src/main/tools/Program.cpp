//
// Created by Khyber on 4/12/2019.
//

#include "src/main/tools/Program.h"

#include "src/share/stde/c_str.h"

#include <unistd.h>
#include <wait.h>

void Program::exec() {
    std::vector<const char*> argv;
    argv.reserve(args.size() + 2);
    argv.emplace_back(name.data());
    for (const auto& arg : args) {
        argv.emplace_back(stde::c_str(arg));
    }
    argv.emplace_back(nullptr);
    if (execvp(name.data(), const_cast<char* const*>(argv.data())) == -1) {
        exit(errno);
    } else {
        exit(0);
    }
}

int Program::awaitOrCatchForkExec() {
    pid_t pid = fork();
    if (pid == 0) {
        exec();
    } else {
        int status;
        waitpid(pid, &status, 0);
        return status;
    }
}

void Program::awaitForkExec() {
    const int status = awaitOrCatchForkExec();
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return;
    }
    exit(status);
}
