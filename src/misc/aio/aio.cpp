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
    
//    char* data = new char[1000000];
//    write(fd, data, 1000000);
//    delete[] data;

//    std::cout << pool.size() << std::endl;
}

void ioTest(llvm::ArrayRef<std::string> ss) {
    const int fd = open("io.out.txt", O_WRONLY | O_CREAT, 0600);
    auto writer = Writer(fd);
    WriteBuffer<char> buffer(std::move(writer));
    
    size_t j = 0;
    for (const auto& s : ss) {
        j++;
//        std::cout << j++ << std::endl;
//        for (const auto c : s) {
//            buffer(c);
//        }
//        for (auto it = s.begin(); it != s.end(); ++it) {
//            const char c = *it;
//            buffer(c);
//        }
        size_t n = s.size();
        for (size_t i = 0; i < n; i++) {
            const char c = s[i];
            buffer(c);
        }
        buffer('\n');
    }
    
}

void g(llvm::ArrayRef<std::string> ss) {
    using namespace std::chrono;
//    std::vector<std::string> ss2(ss.begin(), ss.end());
//    std::cout << " io: " << measure<nanoseconds>::time(ioTest, ss) << std::endl;
    std::cout << "aio: " << measure<nanoseconds>::time(aioTest, ss) << std::endl;
}

void f(u32 n) {
//    std::cout << "io buffer size: " << WriteBuffer<char>::bufferSize << std::endl;
    
    std::vector<std::string> v;
    v.reserve(n);
    for (u32 i = 0; i < n; i++) {
        v.push_back(std::to_string(i));
    }
    
    for (int i = 0; i < 10; i++) {
        g(v);
    }

//    std::cout << " io: " << measure<nanoseconds>::time(ioTest, v) << std::endl;
//    std::cout << "aio: " << measure<nanoseconds>::time(aioTest, v) << std::endl;
}

int main(int argc, const char* const* argv) {
    u32 n = 10000;
    if (argc >= 2) {
        std::stringstream ss(argv[1]);
        ss >> n;
    }
    for (int i = 0; i < 10; i++) {
        f(n);
    }
//    sleep(1);
}
