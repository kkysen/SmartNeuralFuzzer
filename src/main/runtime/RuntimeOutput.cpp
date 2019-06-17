//
// Created by Khyber on 4/7/2019.
//

#include "src/main/runtime/RuntimeOutput.h"

#include "src/share/stde/addStrings.h"
#include "src/share/hook/libc/syscall/getpid.h"
#include "src/share/hook/libc/syscall/gettid.h"
#include "src/share/io/env/Argv.h"

namespace {
    
    fse::Dir getDir(std::string_view name) {
        using namespace std::string_literals;
        using stde::string::operator+;
        return fse::Dir()
                .dir(name + ".out.dir"s)
                .dir(std::string(env::Argv::get().programName()))
                .dir(std::to_string(syscalls::getpid()))
                .dir(std::to_string(syscalls::gettid()));
    }
    
}

namespace runtime {
    
    RuntimeOutput::RuntimeOutput(std::string_view name) noexcept
            : name(name), dir(getDir(name)) {}
    
}
