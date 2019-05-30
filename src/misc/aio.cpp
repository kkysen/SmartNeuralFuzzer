//
// Created by Khyber on 5/26/2019.
//

#include "src/share/aio/StandardWriteBuffer.h"
#include "src/share/io/WriteBuffer.h"

#include "llvm/ADT/ArrayRef.h"

#include <iostream>

using namespace aio;
using namespace io;

bool fatal = false;

void onFatalError(const std::error_code&) {
    fatal = true;
}

template <typename TimeT = std::chrono::milliseconds>
struct measure {
    template <typename F, typename ...Args>
    static typename TimeT::rep time(F&& func, Args&& ... args) {
        const auto start = std::chrono::steady_clock::now();
        std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
        const auto end = std::chrono::steady_clock::now();
        const auto duration = std::chrono::duration_cast<TimeT>(end - start);
        return duration.count();
    }
};

void aioTest(llvm::ArrayRef<std::string> ss) {
    WriteBufferPool<onFatalError, 2, char> pool;
    const int fd = open("aio.out.txt", O_WRONLY | O_CREAT, 0600);
    auto buffer = pool.request<StandardWriteBuffer, char>()(fd);
    
    for (const auto& s : ss) {
        for (const auto c : s) {
            buffer(c);
        }
        buffer('\n');
    }
    
    char* data = new char[1000000];
    write(fd, data, 1000000);
    
//    std::cout << pool.size() << std::endl;
}

void ioTest(llvm::ArrayRef<std::string> ss) {
    const int fd = open("io.out.txt", O_WRONLY | O_CREAT, 0600);
    auto writer = Writer(fd);
    WriteBuffer<char> buffer(std::move(writer));
    
    for (const auto& s : ss) {
        for (const auto c : s) {
            buffer.on(c);
        }
        buffer.on('\n');
    }
    
}

void f(u32 n) {
    std::vector<std::string> v;
    v.reserve(n);
    for (u32 i = 0; i < n; i++) {
        v.push_back(std::to_string(i));
    }
    
    using namespace std::chrono;
    
    std::cout << "aio: " << measure<nanoseconds>::time(aioTest, v) << std::endl;
    std::cout << " io: " << measure<nanoseconds>::time(ioTest, v) << std::endl;
    
//    std::cout << " io: " << measure<nanoseconds>::time(ioTest, v) << std::endl;
//    std::cout << "aio: " << measure<nanoseconds>::time(aioTest, v) << std::endl;
}

int main(int argc, const char* const* argv) {
    u32 n = 10000;
    if (argc >= 2) {
        std::stringstream ss(argv[1]);
        ss >> n;
    }
    f(n);
//    sleep(1);
}
