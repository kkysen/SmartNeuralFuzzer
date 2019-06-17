//
// Created by Khyber on 3/22/2019.
//

#include "src/share/io/fse.h"

#include "src/share/common/hardAssert.h"

#ifndef __EXCEPTIONS
#include "llvm/Support/ErrorHandling.h"
#endif

#include <iostream>

namespace fse {
    
    fs::filesystem_error error(const std::string& what) {
        return fs::filesystem_error(what, std::error_code(errno, std::system_category()));
    }
    
    fs::filesystem_error error(const std::string& what, const fs::path& path1) {
        return fs::filesystem_error(what, path1, std::error_code(errno, std::system_category()));
    }
    
    fs::filesystem_error error(const std::string& what, const fs::path& path1, const fs::path& path2) {
        return fs::filesystem_error(what, path1, path2, std::error_code(errno, std::system_category()));
    }
    
    void* mmapRaw(int fd, int protection, int flags, size_t length, size_t offset) {
        if (length == 0) {
            return nullptr;
        }
        void* memory = ::mmap(nullptr, length, protection, flags, fd, offset);
        if (memory == MAP_FAILED) {
            _throw(error("mmap failed for fd = " + std::to_string(fd)));
        }
        return memory;
    }
    
    bool ensureDir(const fs::path& path) {
        // TODO replace this with a fs:: impl?
        const bool failed = mkdir(path.c_str(), 0755) == -1;
        const bool existed = errno == EEXIST;
        if (failed && !existed) {
            _throw(error("mkdir", path));
        }
        errno = 0;
        return !existed;
    }
    
    void fakeThrow(const std::exception& exception) {
        #ifndef __EXCEPTIONS
        llvm_unreachable(exception.what());
        #else
        __assert_fail(exception.what(), __FILE__, __LINE__, __ASSERT_FUNCTION);
        #endif
    }
    
    void _throw(const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        #ifdef __EXCEPTIONS
        throw exception;
        #else
        fakeThrow(exception);
        #endif
    }
    
}