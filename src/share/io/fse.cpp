//
// Created by Khyber on 3/22/2019.
//

#include "src/share/io/fse.h"

fs::filesystem_error fse::error(const std::string& what) {
    return fs::filesystem_error(what, std::error_code());
}

fs::filesystem_error fse::error(const std::string& what, const fs::path& path1) {
    return fs::filesystem_error(what, path1, std::error_code());
}

fs::filesystem_error fse::error(const std::string& what, const fs::path& path1, const fs::path& path2) {
    return fs::filesystem_error(what, path1, path2, std::error_code());
}

void* fse::mmapRaw(int fd, int protection, int flags, size_t length, size_t offset) {
    if (length == 0) {
        return nullptr;
    }
    void* memory = ::mmap(nullptr, length, protection, flags, fd, offset);
    if (memory == MAP_FAILED) {
        throw error("mmap failed for fd = " + std::to_string(fd));
    }
    return memory;
}
