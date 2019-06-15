//
// Created by Khyber on 6/12/2019.
//

#include "src/share/io/env/Environment.h"
#include "src/share/io/Popen.h"
#include "src/share/io/fse.h"
#include "src/share/stde/addStrings.h"
#include "src/share/stde/compareEnds.h"
#include "src/share/concurrent/numVirtualCores.h"

#include <cstdlib>
#include <fstream>

#include <unistd.h>
#include <wait.h>

namespace {
    
    using namespace std::literals;
    using stde::string::operator+;
    using env::Environment;
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
            return "";
        }
        return line.substr(i + myLDFlags.size());
    }
    
    template <class F>
    auto forkExec(F f) {
        const auto pid = ::fork();
        if (pid == -1) {
            fse::_throw(std::runtime_error("fork"));
        }
        if (pid == 0) {
            f();
            exit(EXIT_SUCCESS);
        } else {
            return [pid]() {
                int status;
                ::waitpid(pid, &status, WEXITED);
                if (WIFEXITED(status) != 0) {
                    fse::_throw(std::runtime_error("waitpid"));
                }
            };
        }
    }
    
    void execConfigure() {
        Environment env;
        
        const auto prepend = [&](const std::string_view var, const std::string_view value) {
            env.modify(var, [=](std::string& old) {
                old = " "s + value + old + " "sv;
            });
        };
        
        env["CC"] = cc;
        env["CXX"] = cxx;
        env["RANLIB"] = ranlib;
        prepend("CFLAGS", "-flto");
        prepend("LDFLAGS", myLDFlags);
        
        env.exec("./configure");
    }
    
    void runConfigure() {
        forkExec(execConfigure)();
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
        forkExec([]() {
            Environment::exec(::environ, "ninja", "-C", BUILD_PATH, "main");
        })();
    }
    
    void runMake() {
        forkExec([]() {
            const auto parallelism = std::to_string(concurrent::numVirtualCores);
            Environment::exec(::environ, "make", "-j", parallelism.c_str());
        })();
    }
    
    void execFuzzMake(std::string_view _target, std::string_view originalLDFlags) {
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
        
        Environment env;
        
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
        
        env.exec("make", "-f", BIN_PATH_FUZZ_AUTOTOOLS_DIR "/FuzzMakefile");
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
    
    auto compileTarget(std::string_view target, std::string_view originalLDFlags) {
        const auto wait = forkExec([=]() {
            execFuzzMake(target, originalLDFlags);
        });
        return [=]() {
            wait();
            renameSourceMap(target);
        };
    }
    
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
        llvm::SmallVector<decltype(compileTarget(""sv, ""sv)), 0> waits;
        forEachTarget([originalLDFlags, &waits](const std::string_view target) {
            waits.push_back(compileTarget(target, originalLDFlags));
        });
        for (const auto& wait : waits) {
            wait();
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
    
    void run(int argc, const char* const* argv) {
        tryClean(argc, argv);
        
        std::fstream originalLDFlagsCache("__LDFLAGS.txt");
        std::string originalLDFlags;
        if (originalLDFlagsCache) {
            originalLDFlagsCache >> originalLDFlags;
        } else {
            runConfigure();
            originalLDFlags = removeADotOutAndGetOriginalLDFlags();
        }
        
        runMake();
        runNinja();
        compile(originalLDFlags);
    }
    
}

int main(int argc, const char* const* argv) {
    run(argc, argv);
    return EXIT_SUCCESS;
}
