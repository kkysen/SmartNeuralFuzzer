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
        const std::string_view path; // just for error messages
    
    public:
        
        explicit Reader(int fd, std::string_view path) noexcept
                : fd(fd), stats(Stat::fd(fd)), path(path) {}
    
    private:
        
        void error(const std::string& what) const {
            fse::_throw(fse::error(what, path));
        }
        
        void invalidFileType() const {
            error("invalid file type for reading: "s + stats.type.toString());
        }
        
        void error() const {
            error("read");
        }
        
        std::string allAtOnce() const {
            std::string s;
            s.reserve(stats.size());
            const ssize_t n = ::read(fd, s.data(), stats.size());
            if (n == -1 || static_cast<size_t>(n) != stats.size()) {
                error();
            }
            return s;
        }

    public:
        
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

    private:
        
        std::string linked() const {
            return io::readAll(allAtOnce());
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
                case FileType::regular:
                    return allAtOnce();
                case FileType::fifo:
                case FileType::socket:
                    return buffered();
                case FileType::symlink:
                    return linked();
            }
        }
        
    };
    
    
    
}

namespace io {
    
    std::string readAll(int fd) {
        const std::string pathLike = "[fd="s + std::to_string(fd) + "]"sv;
        return Reader(fd, pathLike).all();
    }
    
    std::string readAll(const char* path) {
        const int fd = ::open(path, O_RDONLY);
        if (fd == -1) {
            fse::_throw(fse::error("open", path));
        }
        const auto reader = Reader(fd, path);
        const std::string looksEmptyDir = "/proc/";
        const bool looksEmpty = ::strncmp(path, looksEmptyDir.data(), looksEmptyDir.size()) == 0;
        // buffered will always read all of it
        const auto all = looksEmpty ? reader.buffered() : reader.all();
        close(fd);
        return all;
    }
    
}
