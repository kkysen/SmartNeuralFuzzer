//
// Created by Khyber on 7/25/2019.
//

#include "src/share/stde/addStrings.h"
#include "src/share/stde/compareEnds.h"

#include <tuple>

#include <unistd.h>

constexpr std::tuple<bool, std::string_view, std::string_view> parseProgramName(std::string_view programName) noexcept {
    const std::string_view prefixes[] = {"opt-" LLVM_VERSION_MAJOR, "opt"};
    const auto slashIndex = programName.find_last_of('/');
    constexpr auto npos = std::string::npos;
    const auto start = slashIndex == npos ? 0 : slashIndex + 1;
    const auto s = programName.substr(start);
    for (const auto prefix : prefixes) {
        const auto i = prefix.size();
        if (stde::startsWith(s, prefix) && s[i] == '.') {
            return {true, s.substr(0, i), s.substr(i + 1)};
        }
    }
    return {false, {}, {}};
}

void exec(const char* const* argv) {
    char* const* _argv = const_cast<char* const*>(argv);
    execvp(_argv[0], _argv);
}

void run(int oldArgc, const char* const* oldArgv) {
    if (oldArgc < 1) {
        return;
    }
    
    const auto[found, optName, passName] = parseProgramName(oldArgv[0]);
    if (!found) {
        return;
    }
    
    const size_t argc = oldArgc + 3;
    const char* argv[argc + 1];
    argv[argc] = nullptr;
    size_t i = 0;
    
    using namespace std::literals;
    using stde::string::operator+;
    
    #define arg(var, value) \
        const auto var = ""s + value; \
        argv[i++] = var.c_str()
    
    arg(ownOptName, optName);
    argv[i++] = "-load";
    
    const auto pass = "pass."s + passName;
    arg(loadPassArg, BUILD_PATH
            "/lib/lib"sv + pass + ".so");
    arg(runPassArg, "-"sv + pass);
    
    const bool specialCase = oldArgc == 3 && std::string_view(oldArgv[1]) == "";
    if (specialCase) {
        const std::string_view target = oldArgv[2];
        arg(input, target + ".0.5.precodegen.bc"sv);
        argv[i++] = "-o";
        arg(output, target + ".0.6."sv + passName + ".bc"sv);
        argv[i] = nullptr;
        return exec(argv);
    }
    
    #undef arg
    
    std::copy(oldArgv + 1, oldArgv + oldArgc, argv + i);
    
    return exec(argv);
}

int main(int argc, const char* const* argv) {
    run(argc, argv);
    return EXIT_FAILURE;
}
