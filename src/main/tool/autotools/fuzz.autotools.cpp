//
// Created by Khyber on 6/12/2019.
//

#include "src/share/io/env/Environment.h"
#include "src/share/io/env/Exec.h"
#include "src/share/io/Popen.h"
#include "src/share/io/fse.h"
#include "src/share/stde/addStrings.h"
#include "src/share/stde/compareEnds.h"
#include "src/share/concurrent/numVirtualCores.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include <unistd.h>
#include <wait.h>

namespace {
    
    using namespace std::literals;
    using stde::string::operator+;
    using env::Environment;
    using env::Exec;
    using io::Popen;
    
    #define FLTO "-flto -fuse-ld=lld"
    
    constexpr auto flto = FLTO ""sv; // flto makes .o files .bc files
    constexpr auto myLDFlags = FLTO "-Wl,-plugin-opt=save-temps"sv; // generates .bc files also
    
    #undef FLTO
    
    constexpr auto cc = "clang"sv;
    constexpr auto cxx = "clang++"sv;
    constexpr auto ranlib = "llvm-ranlib"sv;
    
    constexpr auto targetSuffix = ".0.5.precodegen.bc"sv;
    
    void removeADotOut(const fs::path& dir) {
        std::cout << "rm -rf a.out.*" << std::endl;
        for (const auto& entry: fs::recursive_directory_iterator(dir)) {
            const std::string_view path = entry.path().filename().string();
            if (stde::startsWith(path, "a.out."sv)) {
                fs::remove(entry.path());
            }
        }
    }
    
    constexpr std::string_view findOriginalLDFlags(std::string_view line) noexcept {
        const auto i = line.find(myLDFlags);
        if (i == std::string_view::npos) {
            // this method doesn't always work
            // in this case, the user will have to set this themselves
            std::cout << "couldn't find original LDFLAGS in Makefile" << std::endl;
            return "";
        }
        std::cout << "found original LDFLAGS=" << myLDFlags << std::endl;
        return line.substr(i + myLDFlags.size());
    }
    
    template <class F>
    auto forkExec(F f) {
        const auto pid = ::fork();
        switch (pid) {
            case -1:
                fse::_throw(std::runtime_error("fork"));
            case 0: {
                std::cout << "running" << std::endl;
                f();
                exit(EXIT_SUCCESS);
            }
            default: {
                return [pid]() {
                    int status;
                    std::cout << "waiting" << std::endl;
                    std::cout << ::waitpid(pid, &status, 0) << std::endl;
                    perror("waitpid");
                    std::cout << "waited" << std::endl;
                    const int exitCode = WIFEXITED(status);
                    std::cout << "exitCode: " << exitCode << std::endl;
                    if (exitCode != 0) {
                        fse::_throw(std::runtime_error(
                                "waitpid(exitCode=" + std::to_string(exitCode) + ")"));
                    }
                };
            }
        }
    }
    
//    void execConfigure() {
//        Environment env;
//
//        const auto prepend = [&](const std::string_view var, const std::string_view value) {
//            env.modify(var, [=](std::string& old) {
//                old = " "s + value + old + " "sv;
//            });
//        };
//
//        env["CC"] = cc;
//        env["CXX"] = cxx;
//        env["RANLIB"] = ranlib;
//        prepend("CFLAGS", "-flto");
//        prepend("LDFLAGS", myLDFlags);
//
//        Exec("./configure")
//                .print(std::cout)
//                .exec(env);
//    }
    
    void runConfigure() {
//        forkExec(execConfigure)();
        Environment currentEnv;
        auto env = Environment::empty();
        const auto prepend = [&](const std::string_view var, const std::string_view value) {
            env[var] = " "s + value + currentEnv.get(var, "") + " "sv;
        };
        env["CC"] = cc;
        env["CXX"] = cxx;
        env["RANLIB"] = ranlib;
        prepend("CFLAGS", "-flto");
        prepend("LDFLAGS", myLDFlags);
        Popen("./configure", env);
    }
    
    std::string_view removeADotOutAndGetOriginalLDFlags() {
        Popen traceMakeProcess("make -n");
        removeADotOut(".");
        
        // process after to run `rm -f a.out.*` in parallel
        std::string_view lastLine;
        traceMakeProcess.forEachLine([&lastLine](const std::string_view line) {
            lastLine = line;
        });
        traceMakeProcess.close();
        
        return findOriginalLDFlags(lastLine);
    }
    
    void runNinja() {
        Popen("ninja -C " BUILD_PATH " main"); // NOLINT(bugprone-unused-raii)
//        forkExec([]() {
////            Exec("ninja", "-C", BUILD_PATH, "main")
//                Exec("/bin/sh", "-c", "ninja -C " BUILD_PATH " main")
//                    .print(std::cout)
//                    .exec();
//        })();
    }
    
    void runMake() {
        Popen("make -j " + std::to_string(concurrent::numVirtualCores));
//        forkExec([]() {
//            const auto parallelism = std::to_string(concurrent::numVirtualCores);
//            Exec("make", "-j", parallelism.c_str())
//                    .print(std::cout)
//                    .exec();
//        })();
    }
    
//    void execFuzzMake(std::string_view _target, std::string_view originalLDFlags) {
//        #define buildDir BIN_PATH
//        #define libDir buildDir "/lib"
//        #define binDir buildDir "/bin"
//        #define lib libDir "/lib"
//        #define libPassCoverage lib "pass.coverage."
//        #define block libPassCoverage "block.so"
//        #define branch libPassCoverage "branch.so"
//
//        constexpr auto passes = block " " branch ""sv;
//        constexpr auto loadPasses = "-load=" block " -load=" branch ""sv;
//        constexpr auto runtimes = lib "runtime.coverage.bc"sv;
//
//        constexpr auto opt = binDir "/opt-9"sv;
//        constexpr auto link = "llvm-link"sv;
//        constexpr auto optLevel = "-O3"sv;
//
//        const std::string target(_target);
//
//        const auto src = target + ".0.5.precodegen.bc";
//        const auto obj = target + ".coverage.o"sv;
//
//        Environment env;
//
//        const auto libraries = "-lstdc++ -lstdc++fs -pthread -ldl -L"s + env["CLANG_HOME"] + "/lib -lLLVMSupport"sv;
//
//        #define _(var) env[""#var] = var
//
//        env["bc"] = target + "0.6.coverage.bc"sv;
//        env["all"] = target + ".coverage.bc"sv;
//        _(obj);
//        env["exe"] = target + ".coverage"sv;
//
//        _(cc);
//        _(opt);
//        _(link);
//        _(optLevel);
//
//        env["dependencies"] = src + " "sv + passes;
//        env["optArgs"] = ""s + loadPasses + " "sv + src;
//        _(runtimes);
//        env["linkArgs"] = ""s + flto + obj + libraries + originalLDFlags;
//
//        #undef _
//
//        #undef buildDir
//        #undef libDir
//        #undef binDir
//        #undef lib
//        #undef libPassCoverage
//        #undef block
//        #undef branch
//
//        Exec("make", "-f", BIN_PATH_FUZZ_AUTOTOOLS_DIR "/FuzzMakefile")
//                .print(std::cout)
//                .exec(env);
//    }
    
    Popen runFuzzMake(std::string_view _target, std::string_view originalLDFlags) {
        #define buildDir BIN_PATH
        #define libDir buildDir "/lib"
        #define binDir buildDir "/bin"
        #define lib libDir "/lib"
        #define libPassCoverage lib "pass.coverage."
        #define block libPassCoverage "block.so"
        #define branch libPassCoverage "branch.so"
        
        constexpr auto passes = block " " branch ""sv;
        constexpr auto loadPasses = "-load=" block " -load=" branch ""sv;
        constexpr auto runtimes = lib "runtime.coverage.bc"sv;
        
        constexpr auto opt = binDir "/opt-9"sv;
        constexpr auto link = "llvm-link"sv;
        constexpr auto optLevel = "-O3"sv;
        
        const std::string target(_target);
        
        const auto src = target + ".0.5.precodegen.bc";
        const auto obj = target + ".coverage.o"sv;
        
        auto env = Environment::empty();
        
        const auto libraries = "-lstdc++ -lstdc++fs -pthread -ldl -L"s + env["CLANG_HOME"] + "/lib -lLLVMSupport"sv;
        
        #define _(var) env[""#var] = var
        
        env["bc"] = target + "0.6.coverage.bc"sv;
        env["all"] = target + ".coverage.bc"sv;
        _(obj);
        env["exe"] = target + ".coverage"sv;
        
        _(cc);
        _(opt);
        _(link);
        _(optLevel);
        
        env["dependencies"] = src + " "sv + passes;
        env["optArgs"] = ""s + loadPasses + " "sv + src;
        _(runtimes);
        env["linkArgs"] = ""s + flto + obj + libraries + originalLDFlags;
        
        #undef _
        
        #undef buildDir
        #undef libDir
        #undef binDir
        #undef lib
        #undef libPassCoverage
        #undef block
        #undef branch
        
        return Popen("make -f " BIN_PATH_FUZZ_AUTOTOOLS_DIR "/FuzzMakefile", env);
    }
    
    void renameSourceMap(std::string_view target) {
        constexpr auto ext = ".blocks.map"sv;
        const auto oldPath = "ld-temp.o"s + ext;
        const auto newPath = ""s + target + ext;
        errno = 0;
        if (::rename(oldPath.c_str(), newPath.c_str()) == -1) {
            if (errno == ENOENT) {
                errno = 0;
            } else {
                fse::_throw(fse::error("rename", oldPath, newPath));
            }
        }
    }
    
//    auto compileTargetOld(std::string_view target, std::string_view originalLDFlags) {
//        const auto wait = forkExec([=]() {
//            execFuzzMake(target, originalLDFlags);
//        });
//        return [=]() {
//            wait();
//            renameSourceMap(target);
//        };
//    }
    
//    auto compileTarget(std::string_view target, std::string_view originalLDFlags) {
//        const Popen popen = runFuzzMake(target, originalLDFlags);
//        const auto x = std::move(popen);
//        const auto y = std::make_unique<Popen>(runFuzzMake(target, originalLDFlags));
//        return [target, p = std::move(popen)]() mutable {
//            p->close();
//            renameSourceMap(target);
//        };
//    }
    
    template <class F>
    void forEachTarget(F f) {
        for (const auto& entry : fs::recursive_directory_iterator()) {
            entry.path().filename();
            const std::string_view path = entry.path().filename().string();
            if (stde::endsWith(path, targetSuffix)) {
                const auto target = path.substr(0, path.size() - targetSuffix.size());
                f(target);
            }
        }
    }
    
    void compile(std::string_view originalLDFlags) {
        llvm::SmallVector<std::pair<Popen, std::string>, 0> waits;
        forEachTarget([originalLDFlags, &waits](const std::string_view target) {
            waits.emplace_back(runFuzzMake(target, originalLDFlags), target);
//            waits.push_back(compileTarget(target, originalLDFlags));
        });
        for (auto& wait : waits) {
            auto& [popen, target] = wait;
            popen.close();
            renameSourceMap(target);
//            wait();
        }
    }
    
    void tryClean(int argc, const char* const* argv) {
        if (argc > 1) {
            const std::string_view cleanOption = argv[1];
            if (cleanOption == "-clean"sv) {
                fse::_throw(std::runtime_error("-clean not implemented yet"));
            }
        }
    }
    
    void prompt(std::string_view prompt) {
        std::cout << "prompt: " << prompt << std::endl;
        char c;
        std::cin >> c;
    }
    
    void run(int argc, const char* const* argv) {
        tryClean(argc, argv);
        
        prompt("runNinja!");
        runNinja();
        
        prompt("LDFLAGS");
        std::fstream originalLDFlagsCache("__LDFLAGS.txt");
        std::string originalLDFlags;
        if (originalLDFlagsCache) {
            std::cout << "found original LDFLAGS; already configured" << std::endl;
            originalLDFlagsCache >> originalLDFlags;
        } else {
            std::cout << "couldn't find original LDFLAGS; configuring" << std::endl;
            prompt("runConfigure");
            runConfigure();
            prompt("rm -f a.out.* && getOriginalLDFlags");
            originalLDFlags = removeADotOutAndGetOriginalLDFlags();
            originalLDFlagsCache << originalLDFlags;
        }
        
        prompt("runMake");
        runMake();
        
        prompt("compile");
        compile(originalLDFlags);
    }
    
}

int main(int argc, const char* const* argv) {
    run(argc, argv);
    return EXIT_SUCCESS;
}
