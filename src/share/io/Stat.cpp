//
// Created by Khyber on 5/20/2019.
//

#include "src/share/io/Stat.h"

namespace io {
    
    Stat Stat::file(const char* pathName) {
        return generic(::stat, pathName);
    }
    
    Stat Stat::fd(int fd) {
        return generic(::fstat, fd);
    }
    
    Stat Stat::link(const char* pathName) {
        return generic(::lstat, pathName);
    }
    
    Stat Stat::at(int dirFd, const char* pathName, int flags) {
        // fstatat doesn't conform to the stat function argument pattern
        struct stat statBuf = {};
        const bool failed = ::fstatat(dirFd, pathName, &statBuf, flags) == -1;
        const int error = failed ? errno : 0;
        if (failed) {
            errno = 0;
        }
        return Stat(statBuf, error);
    }
    
    Stat Stat::linked(int _fd) {
        const auto stats = fd(_fd);
        if (!stats.type.is.symlink()) {
            return stats;
        }
        using namespace std::literals;
        return file("/proc/self/fd/"s + std::to_string(_fd));
    }
    
}
