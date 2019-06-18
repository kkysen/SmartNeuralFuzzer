//
// Created by Khyber on 6/13/2019.
//

#include "src/share/io/readAll.h"

#include "src/share/io/Stat.h"
#include "src/share/stde/addStrings.h"

namespace {
    
    using namespace std::literals;
    using stde::string::operator+;
    
    using io::Stat;
    
    class Reader {
    
    private:
        
        const int fd;
        const Stat stats;
        const char* path;
    
    public:
        
        explicit Reader(int fd, const char* path = nullptr) noexcept
                : fd(fd),
                  stats(path ? Stat::file(path) : Stat::linked(fd)),
                  path(path) {}
    
    private:
        
        std::string getPath() const {
            if (path) {
                return path;
            }
            const auto linkPath = "/proc/self/fd/"s + std::to_string(fd);
            const auto linkStats = Stat::link(linkPath);
            char link[linkStats.size()];
            const ssize_t n = ::readlink(linkPath.c_str(), link, sizeof(link));
            if (n == -1) {
                fse::_throw(fse::error("readlink"));
            }
            return std::string(link, static_cast<size_t>(n));
        }
        
        void error(const std::string& what) const {
            fse::_throw(fse::error(what, getPath()));
        }
        
        void invalidFileType() const {
            error("invalid file type for reading: "s + stats.type.toString());
        }
        
        void error() const {
            error("read");
        }
        
        std::string allAtOnce() const {
            if (stats.id.device.isProc()) {
                // /proc/ files appear empty but aren't
                return buffered();
            }
            std::string s;
            s.resize(stats.size());
            const ssize_t n = ::read(fd, s.data(), stats.size());
            if (n == -1 || static_cast<size_t>(n) != stats.size()) {
                error();
            }
            return s;
        }
        
        std::string buffered() const {
            std::ostringstream ss;
            char buffer[stats.blockSize];
            ssize_t n;
            do {
                n = ::read(fd, buffer, sizeof(buffer));
                if (n == -1) {
                    error();
                }
                ss.write(buffer, n);
            } while (n != 0);
            return ss.str();
        }
    
    public:
        
        std::string all() const {
            using io::FileType;
            switch (stats.type.raw()) {
                case FileType::none:
                case FileType::notFound:
                case FileType::unknown:
                case FileType::block:
                case FileType::character:
                case FileType::directory: {
                    invalidFileType();
                }
                case FileType::symlink: {
                    // symlink is impossible here b/c we specifically skipped it
                    invalidFileType();
                }
                case FileType::regular:
                    return allAtOnce();
                case FileType::fifo:
                case FileType::socket:
                    return buffered();
            }
        }
        
    };
    
    
    
}

namespace io {
    
    std::string readAll(int fd) {
        return Reader(fd).all();
    }
    
    std::string readAll(const char* path) {
        const int fd = ::open(path, O_RDONLY);
        if (fd == -1) {
            fse::_throw(fse::error("open", path));
        }
        const auto all = Reader(fd, path).all();
        close(fd);
        return all;
    }
    
}
