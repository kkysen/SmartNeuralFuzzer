//
// Created by Khyber on 4/7/2019.
//

#include "src/share/io/Dir.h"

namespace fse {
    
    Dir::Dir(const fs::path& path) : fd(ensureDir(path)) {}
    
    Dir::~Dir() {
        if (fd >= 0) {
            // skip -1 and AT_FDCWD (-100)
            close(fd);
        }
    }
    
    Dir Dir::dir(const std::string& dirName, mode_t mode) const {
        if (mkdirat(fd, dirName.c_str(), mode) == -1) {
            if (errno != EEXIST) {
                throw fse::error("mkdirat", dirName);
            } else {
                errno = 0;
            }
        }
        const int dirFd = openat(fd, dirName.c_str(), O_DIRECTORY | O_PATH);
        if (dirFd == -1) {
            throw fse::error("openat", dirName);
        }
        return Dir(dirFd);
    }
    
    int Dir::file(const std::string& fileName, int flags, mode_t mode) const {
        const int fileFd = openat(fd, fileName.c_str(), flags, mode);
        if (fileFd == -1) {
            throw fse::error("openat", fileName);
        }
        return fileFd;
    }
    
}
