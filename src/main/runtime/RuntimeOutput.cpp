//
// Created by Khyber on 4/7/2019.
//

#include "src/main/runtime/RuntimeOutput.h"

#include "src/share/stde/addStrings.h"
#include "src/share/hook/libc/syscall/getpid.h"
#include "src/share/hook/libc/syscall/gettid.h"
#include "src/share/io/Argv.h"

namespace {
    
    std::string_view getProgramName() {
        const auto fullProgramName = io::Argv::get()[0];
        const auto i = fullProgramName.find_last_of('/');
        const auto j = i == std::string_view::npos ? 0 : i + 1;
        return fullProgramName.substr(j);
    }
    
    fse::Dir getDir(std::string_view name) {
        using namespace std::string_literals;
        using stde::string::operator+;
        return fse::Dir()
                .dir(name + ".out.dir"s)
                .dir(std::string(getProgramName()))
                .dir(std::to_string(syscalls::getpid()))
                .dir(std::to_string(syscalls::gettid()));
    }
    
}

namespace runtime {
    
    RuntimeOutput::RuntimeOutput(std::string_view name) noexcept
            : name(name), dir(getDir(name)) {}
    
}
