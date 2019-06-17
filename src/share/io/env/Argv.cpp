//
// Created by Khyber on 6/12/2019.
//

#include "src/share/io/env/Argv.h"

#include "src/share/stde/split.h"
#include "src/share/io/readAll.h"

#include <memory>

#include <iostream>

namespace {
    
    using namespace env;
    
    std::string_view getProgramName(std::string_view fullProgramName) {
        const auto i = fullProgramName.find_last_of('/');
        const auto j = i == std::string_view::npos ? 0 : i + 1;
        return fullProgramName.substr(j);
    }
    
    std::string makeRaw(ArrayView<std::string_view> args) {
        size_t n = 0;
        for (const auto arg : args) {
            n += arg.size() + 1;
        }
        std::string raw;
        raw.reserve(n);
        for (const auto arg : args) {
            raw += arg;
            raw += '\0';
        }
        raw.pop_back();
        return raw;
    }
    
    std::string makeRaw(int argc, const char* const* argv) {
        std::string raw;
        for (const auto arg : ArrayView(argv, argc)) {
            raw += arg;
            raw += '\0';
        }
        raw.pop_back();
        return raw;
    }
    
    std::string readArgv() {
        std::string raw = io::readAll("/proc/self/cmdline");
        for (auto& c : raw) {
            if (c == ' ') {
                c = '\0';
            }
        }
        return raw;
    }
    
    std::unique_ptr<Argv> argv = nullptr;
    
}

namespace env {
    
    Argv::Argv(std::string _raw, size_t argc) : raw(std::move(_raw)) {
        args.reserve(argc);
        stde::split(std::string_view(raw), '\0', [this](const std::string_view arg) {
            args.push_back(arg);
        });
        _programName = getProgramName(args[0]);
    }
    
    Argv::Argv(std::string raw, Argv::Key) : Argv(std::move(raw), 0) {}
    
    Argv::Argv(ArrayView<std::string_view> args) : Argv(makeRaw(args), args.size()) {}
    
    Argv::Argv(int argc, const char* const* argv) : Argv(makeRaw(argc, argv), argc) {}
    
    const Argv& Argv::get() {
        if (!argv) {
            argv = std::make_unique<Argv>(readArgv(), Key());
        }
        return *argv;
    }
    
}
