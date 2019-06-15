//
// Created by Khyber on 5/20/2019.
//

#pragma once

#include "src/share/time/TimeSpec.h"
#include "src/share/io/fs.h"
#include "src/share/io/fse.h"
#include "src/share/common/numbers.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <experimental/bits/fs_fwd.h>

namespace io {
    
    class FileType {
    
    public:
        
        enum Raw {
            none = 0,
            notFound = -1,
            regular = 1,
            directory = 2,
            symlink = 3,
            block = 4,
            character = 5,
            fifo = 6,
            socket = 7,
            unknown = 8,
        };
        
        class Is {
        
        private:
            
            friend class FileType;
            
            Raw value;
            
            /*implicit*/ constexpr Is(Raw value) noexcept : value(value) {}
        
        public:
            
            #define is(field) \
            constexpr bool field() const noexcept { \
                return value == FileType::field; \
            }
            
            is(none)
            
            is(notFound)
            
            is(regular)
            
            is(directory)
            
            is(symlink)
            
            is(block)
            
            is(character)
            
            is(fifo)
            
            is(socket)
            
            is(unknown)
            
            #undef is
            
        };
        
        Is is;
        
        /*implicit*/ constexpr FileType(Raw value) noexcept : is(value) {}
        
        /*implicit*/ constexpr FileType(fs::file_type type) noexcept : FileType(static_cast<Raw>(type)) {}
        
        constexpr Raw raw() const noexcept {
            return is.value;
        }
        
        /*implicit*/ constexpr operator Raw() const noexcept {
            return raw();
        }
        
        /*implicit*/ constexpr operator fs::file_type() const noexcept {
            return static_cast<fs::file_type>(is.value);
        }
        
        constexpr std::string_view toString() const noexcept {
            #define _(type) case FileType::type: return ""#type
            switch (raw()) {
                _(none);
                _(notFound);
                _(regular);
                _(directory);
                _(symlink);
                _(block);
                _(character);
                _(fifo);
                _(socket);
                _(unknown);
            }
            #undef _
        }
        
        static constexpr FileType fromMode(mode_t mode) noexcept {
            #define __case(macro, type) case macro: return type
            #define _case(_S_IF, type) __case(S_IF##_S_IF, type)
            
            switch (mode & S_IFMT) {
                #ifdef _GLIBCXX_HAVE_S_ISREG
                _case(REG, regular);
                _case(DIR, directory);
                _case(CHR, character);
                _case(BLK, block);
                __case(S_IFIFO, fifo);
                _case(LNK, symlink);
                #ifdef S_IFSOCK
                _case(SOCK, socket);
                #endif
                #endif
                default:
                    return FileType::unknown;
            }
            
            #undef _case
            #undef __case
        }
        
    };
    
}

namespace {
    
    constexpr u32 octal(u8 octetNum, u8 value) {
        return value * (octetNum << (octetNum * 3u));
    }
    
}

namespace io {
    
    class FilePermissions {
        
        #define rwx(o) enum { \
            read = octal(o, 4), \
            write = octal(o, 2), \
            exec = octal(o, 1), \
            all = octal(o, 7), \
        }
    
    public:
        
        enum {
            none = 0,
            all = 0777,
            stickyBit = 01000,
            mask = 07777,
            unknown = 0xFFFF,
            dontFollowSymlink = 0x40000,
        };
        struct owner { rwx(2); };
        struct group { rwx(1); };
        struct others { rwx(0); };
        struct set {
            enum { uid = 04000, gid = 02000 };
        };
        struct permissions {
            enum { add = 0x10000, remove = 0x20000 };
        };
        
        #undef rwx
    
    private:
        
        u32 value;
    
    public:
        
        /*implicit*/ constexpr FilePermissions(u32 value) noexcept : value(value) {}
        
        /*implicit*/ constexpr FilePermissions(fs::perms perms) noexcept : value(static_cast<u32>(perms)) {}
        
        /*implicit*/ constexpr operator u32() noexcept {
            return value;
        }
        
        /*implicit*/ constexpr operator fs::perms() noexcept {
            return static_cast<fs::perms>(value);
        }
        
        static constexpr FilePermissions fromMode(mode_t mode) noexcept {
            return mode & mask;
        }
        
    };
    
}

namespace io {
    
    using _time::TimeSpec;
    
    struct Stat {
        
        struct Device {
            
            union {
                dev_t id;
                struct {
                    // assume little endian
                    u8 minor;
                    u8 major;
                };
            };
            
            /*implicit*/ constexpr Device(dev_t id) noexcept : id(id) {}
            
            // these seem to be the case on the Linux machines I've tested
    
            constexpr bool isProc() const noexcept {
                return major == 0 && minor == 4;
            }
            
            constexpr bool isDev() const noexcept {
                return major == 0 && minor == 6;
            }
            
        };
        
        struct Ids {
            Device device;
            Device deviceType;
            gid_t group;
            uid_t user;
        };
        
        struct LastTimes {
            TimeSpec access;
            TimeSpec modification;
            TimeSpec statusChange;
        };
        
        struct Args {
            int error = 0;
            Ids id;
            ino_t inode;
            FileType type;
            FilePermissions permissions;
            nlink_t numHardLinks;
            off_t signedSize;
            blksize_t blockSize;
            blkcnt_t numBlocks;
            LastTimes lastTime;
        };
        
        int error;
        Ids id;
        ino_t inode;
        FileType type;
        FilePermissions permissions;
        nlink_t numHardLinks;
        off_t signedSize;
        blksize_t blockSize;
        blkcnt_t numBlocks;
        LastTimes lastTime;
        
        /*implicit*/ constexpr Stat(Args args) noexcept
                : error(args.error),
                  id(args.id),
                  inode(args.inode),
                  type(args.type),
                  permissions(args.permissions),
                  numHardLinks(args.numHardLinks),
                  signedSize(args.signedSize),
                  blockSize(args.blockSize),
                  numBlocks(args.numBlocks),
                  lastTime(args.lastTime) {}
        
        /*implicit*/ constexpr Stat(struct stat stat, int error = 0) noexcept : Stat(Args {
                .error = error,
                .id = {
                        .device = stat.st_dev,
                        .deviceType = stat.st_rdev,
                        .group = stat.st_gid,
                        .user = stat.st_uid,
                },
                .inode = stat.st_ino,
                .type = FileType::fromMode(stat.st_mode),
                .permissions = FilePermissions::fromMode(stat.st_mode),
                .numHardLinks = stat.st_nlink,
                .signedSize = stat.st_size,
                .blockSize = stat.st_blksize,
                .numBlocks = stat.st_blocks,
                .lastTime = {
                        .access = stat.st_atim,
                        .modification = stat.st_mtim,
                        .statusChange = stat.st_ctim,
                },
        }) {}
        
        constexpr size_t size() const noexcept {
            return static_cast<size_t>(signedSize);
        }
        
        void check() const {
            if (error != 0) {
                errno = error;
                fse::_throw(fse::error("Stat"));
            }
        }
        
        const Stat& checked() const {
            check();
            return *this;
        }
        
        Stat& checked() {
            check();
            return *this;
        }
        
        template <class StatFunc, class... Args>
        static Stat generic(StatFunc f, Args... args) {
            struct stat statBuf = {};
            const bool failed = f(args..., &statBuf) == -1;
            const int error = failed ? errno : 0;
            if (failed) {
                errno = 0;
            }
            return Stat(statBuf, error);
        }
        
        static Stat file(const char* pathName);
        
        static Stat fd(int fd);
        
        static Stat link(const char* pathName);
        
        static Stat at(int dirFd, const char* pathName, int flags);
        
        // if symlink, stat actual file
        static Stat linked(int fd);
        
        
        template <class String>
        static Stat file(const String& string) {
            return file(string.c_str());
        }
        
        template <class String>
        static Stat link(const String& string) {
            return link(string.c_str());
        }
        
        template <class String>
        static Stat at(int dirFd, const String& string, int flags) {
            return at(dirFd, string.c_str(), flags);
        }
        
    };
    
}
