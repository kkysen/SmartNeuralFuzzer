//
// Created by Khyber on 6/12/2019.
//

#include "src/share/io/Popen.h"
#include "src/share/stde/getline.h"
#include "src/share/stde/addStrings.h"

#include <vector>

#include <fcntl.h>
#include <unistd.h>

std::string escape(std::string_view unescaped) {
    std::string escaped;
    escaped.reserve(unescaped.size() + unescaped.size() / 2);
    for (const auto c : unescaped) {
        if (c == '/') {
            escaped += '\\';
        }
        escaped += c;
    }
    return escaped;
}

void run(bool reset) {
    using namespace std::literals;
    using stde::string::operator+;
    using io::Popen;
    
    // don't need to run repeatedly, just once every time cmake is re-run
    // cmake deletes this file to let us know we should run this again
    const int fd = ::open(BIN_PATH_AR_LOCK, O_RDWR | (reset ? 0 : O_CREAT | O_EXCL), 0600);
    if (fd == -1) {
        if (reset) {
            ::unlink(BIN_PATH_AR_LOCK);
        }
        ::close(fd);
        printf("already %soverrode\n", reset ? "un-" : "");
        return;
    }
    FILE& file = *fdopen(fd, "w+");
    
    auto ar = Popen("which llvm-ar").read();
    if (ar.back() == '\n') {
        ar.pop_back(); // remove trailing '\n'
    }
    
    const auto[find, replace] = !reset
                                ? std::pair(std::move(ar), BIN_PATH_AR ""s)
                                : std::pair(BIN_PATH_AR ""s, std::move(ar));
    
    const auto replaceCommand = "sed -i -e 's/"s + escape(find) + "/"sv + escape(replace) + "/g' "sv;
    std::vector<Popen> replacers; // delay closing so they can run in parallel
    if (!reset) {
        Popen("grep -irl \""s + find + "\" " BIN_PATH""sv)
                .forEachLine([&](const std::string_view line) {
                    if (line.find("CMake") != std::string_view::npos) {
                        return;
                    }
                    const auto path = line;
                    fwrite(path.data(), 1, path.size(), &file);
                    replacers.emplace_back(replaceCommand + path);
                });
    } else {
        stde::forEachLine([&](const std::string_view path) {
            replacers.emplace_back(replaceCommand + path);
        }, file);
        ::unlink(BIN_PATH_AR_LOCK);
    }
    fclose(&file);
    printf("%soverriding llvm-ar\n", reset ? "un-" : "");
}

int main(int argc, char**) {
    run(argc > 1);
}
