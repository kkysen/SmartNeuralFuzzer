//
// Created by Khyber on 3/14/2019.
//

#include "src/main/BranchCoverage/runtime/BranchCoverageRuntime.h"

#include "src/share/common/math.h"
#include "src/share/common/fs.h"

#include <fstream>
#include <algorithm>
#include <cstring>

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

namespace {
    
    class BranchCoverageRuntime {
        
        /*
         * File format:
         *
         *  numSingleBranches: u64;
         *  numMultiBranches: u64;
         *  numInfiniteBranches: u64;
         *  isSingle: u1;
         *      indicator starts each block
         *      encodes if this block is single or multi/infinite
         *      if true,
         *          length: u15;
         *          length encodes number of single branches in a row there are
         *          this is padded, so all isSingles are u64 aligned
         *          most branches will be single, so this is good
         *      if false,
         *          isMulti: u1;
         *              encodes if this block is multi or infinite
         *              if true,
         *                  branchNum: u31;
         *                  numBranches: u31;
         *                  31 bits should be plenty enough to hold numBranches
         *              if false,
         *                  address: u62;
         *                  62 bits is definitely enough to hold any address
         *
         * This always uses native endianness.
         */
    
    private:
        
        static constexpr size_t bufferBytes(size_t bits) {
            return divUp(bits, static_cast<size_t>(64));
        }
        
        static constexpr size_t isSingleBits = 1;
        
        static constexpr size_t singleBranchBits = 16 - isSingleBits;
        static constexpr size_t maxSingleBranches = 1 << singleBranchBits;
        static constexpr size_t singleBranchBufferSize = bufferBytes(maxSingleBranches);
        
        static constexpr size_t nonSingleBranchBits = 64 - isSingleBits;
        static constexpr size_t nonSingleBranchBufferSize = bufferBytes(nonSingleBranchBits);
        
        static constexpr size_t minBufferSize = std::max(singleBranchBufferSize, nonSingleBranchBufferSize);
        static constexpr size_t pageSize = _SC_PAGESIZE;
        static constexpr size_t bufferSize = multipleGreaterThan(pageSize, minBufferSize);
        
        std::array<u64, bufferSize> buffer = {};
        
        struct {
            
            u8 byteBit;
            u16 chunkBit;
            size_t byte;
            size_t lastChunkByte;
            
            constexpr u16 chunkBits() noexcept {
                return (chunkBit << 1) | 0b1; // shift up and set first bit to 1 for isSingle
            }
            
            void resetChunk() noexcept {
                lastChunkByte = byte;
                chunkBit = 0;
                byteBit = 0;
                byteBit = 0;
            }
            
            void resetBuffer() noexcept {
                byte = 0;
                resetChunk();
            }
            
        } index = {};
        
        union {
            struct {
                u64 singleBranches;
                u64 multiBranches;
                u64 infiniteBranches;
            };
            std::array<u64, 3> all;
        } count = {};
        
        struct MMapOutput {
            
            static void* mmap(int fd, size_t length, size_t offset = 0) {
                void* memory = ::mmap(nullptr, length, PROT_WRITE, MAP_SHARED, fd, offset);
                if (!memory) {
                    throw fs::filesystem_error("mmap failed for fd = " + std::to_string(fd), std::error_code());
                }
                return memory;
            }
            
            static constexpr size_t startSize = sizeof(count.all);
            
            const int fd;
            void* const start;
            size_t offset;
            void* pages;
            
            explicit MMapOutput(int fd)
                    : fd(fd),
                      start(mmap(fd, startSize)),
                      offset(0),
                      pages(nullptr) {
                next();
            }
            
            ~MMapOutput() {
                munmap(start, startSize);
                munmap(pages, bufferSize);
            }
            
            void next() {
                if (pages) {
                    munmap(pages, bufferSize);
                }
                pages = mmap(fd, bufferSize, offset);
                offset += bufferSize;
            }
            
        } out;
    
    public:
        
        explicit BranchCoverageRuntime(int fd) : out(fd) {}

    private:

        static int create(const fs::path& file) {
            const int fd = creat(file.c_str(), 0644);
            if (fd == -1) {
                throw fs::filesystem_error(file.string(), std::error_code());
            }
            return fd;
        }
        
    public:
        
        explicit BranchCoverageRuntime(const fs::path& file)
                : BranchCoverageRuntime(create(file)) {}
    
    private:
        
        void writeChunkLength() noexcept {
            const u16 chunkBits = index.chunkBits();
            buffer[index.lastChunkByte] = chunkBits;
            buffer[index.lastChunkByte + 1] = chunkBits >> 8;
        }
        
        void writeBuffer() noexcept {
            std::copy_n(buffer.begin(), index.byte, out.pages);
        }
        
        void writeCounts() noexcept {
            std::copy(count.all.begin(), count.all.end(), out.start);
        }
        
        void flush() {
            writeChunkLength();
            writeBuffer();
            out.next();
            writeCounts();
            index.resetBuffer();
        }
        
        void onNonSingleBranch(u64 value) {
            if (index.byte == minBufferSize) {
                flush();
            }
            buffer[index.byte++] = value;
            if (index.byte == minBufferSize) {
                flush();
            }
            index.resetChunk();
        }
    
    public:
        
        void onSingleBranch(bool value) {
            count.singleBranches++;
            buffer[index.byte] |= 1 << index.byteBit;
            index.byteBit = index.byteBit & static_cast<u8>(8 - 1);
            if (index.byteBit == 1) {
                index.byte++; // keep things aligned
            }
            index.chunkBit++;
            if (index.byte == minBufferSize && index.byteBit == 0) {
                flush();
            }
        }
        
        void onMultiBranch(u32 branchNum, u32 numBranches) {
            count.multiBranches++;
            // first bit is isSingle = false
            // second bit is isMulti = true
            onNonSingleBranch(0b01 | branchNum < 1 | static_cast<u64>(numBranches) << (32 + 2));
        }
        
        void onInfiniteBranch(u64 address) {
            count.infiniteBranches++;
            // first bit is isSingle = false
            // second bit is isMulti = false
            onNonSingleBranch(0b00 | address << 2);
        }
        
    };
    
}

API_BranchCoverage(onSingleBranch)(bool value) {
    printf("BranchCoverage: onBranch: %s\n", value ? "true" : "false");
}

API_BranchCoverage(onMultiBranch)(u32 branchNum, u32 numBranches) {
    printf("BranchCoverage: onMultiBranch: %d/%d\n", branchNum, numBranches);
}

API_BranchCoverage(onInfiniteBranch)(u64 address) {
    printf("BranchCoverage: onInfiniteBranch: %lx\n", address);
}
