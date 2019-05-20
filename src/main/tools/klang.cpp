//
// Created by Khyber on 4/11/2019.
//

#include "src/share/stde/contains.h"
#include "src/main/tools/Program.h"

#include <unistd.h>

namespace {
    
    using namespace std::string_view_literals;
    
    using Args = std::vector<std::string_view>;
    
    void compile(Args& args) {
        if (!stde::contains_if(args.begin(), args.end(), stde::containing("flto"sv))) {
            args.insert(args.begin(), "-flto=thin");
        }
        Program("clang", args).exec();
    }
    
    void removeEquals(Args& args) {
        Args newArgs;
        newArgs.reserve(args.size());
        for (const auto& arg : args) {
            if (arg.size() <= 3 || arg[0] != '-') {
                newArgs.emplace_back(arg);
                continue;
            }
            const auto equalsIndex = arg.find('=', 1);
            if (equalsIndex == Args::value_type::npos || equalsIndex == arg.size()) {
                newArgs.emplace_back(arg);
                continue;
            }
            const auto flag = arg.substr(0, equalsIndex);
            const auto value = arg.substr(equalsIndex + 1);
            newArgs.emplace_back(flag);
            newArgs.emplace_back(value);
        }
        args = newArgs;
    }
    
    std::string_view getOutput(Args& args) {
        auto it = std::find_if(args.begin(), args.end(), stde::containing("-o"sv));
        if (it == args.end()) {
            // where does memory go
            return std::to_string(getpid()).;
        }
        
        {
            auto o = *it;
            const auto oEquals = "-o="sv;
            if (o.substr(0, oEquals.size()) == oEquals) {
                // have to be careful here; all the string_views have to be null-terminated
                // a substring including the end is though
                return o.substr(oEquals.size());
            }
        }
        
        return it[1];
    }
    
    void link(Args& args) {
        removeEquals(args);
        const auto output = getOutput(args);
        args.emplace_back(output); // TODO FIXME
        
        Program("llvm-link", args).awaitForkExec(); // llvm-link, and add runtimes
        Program("opt", args).awaitForkExec(); // opt -O3
        Program("opt", args).awaitForkExec(); // opt -load passes
        Program("opt", args).awaitForkExec(); // opt -O3
        Program("clang", args).awaitForkExec();
    }
    
    void run(Args& args) {
        const bool linking = stde::contains(args.begin(), args.end(), "-c");
        (!linking ? compile : link)(args);
    }
    
}

int main(int argc, const char** argv) {
    if (argc == 0) {
        return EXIT_FAILURE;
    }
    
    Args args(argv + 1, argv + argc);
    run(args);
    return EXIT_SUCCESS;
}
