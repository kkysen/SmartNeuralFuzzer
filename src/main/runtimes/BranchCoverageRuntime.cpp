//
// Created by Khyber on 3/14/2019.
//

#include "BranchCoverageRuntime.h"

#include "src/share/common/math.h"
#include "src/share/common/fs.h"
#include "src/share/common/fse.h"

#include <fstream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <numeric>

namespace {
    
    // can't have constexpr statics based on static constexpr functions in same class
    // so have to define them at the file level
    
    constexpr size_t minBytesForBits(size_t bits) noexcept {
        return math::divUp(bits, static_cast<size_t>(CHAR_BIT));
    }
    
    /**
     * File format:
     *
     *  numSingleBranches: u64;
     *  numMultiBranches: u64;
     *  numInfiniteBranches: u64;
     *
     *  after this is all repeated
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
    class BranchCoverageRuntime {
    
    private:
        
        static constexpr size_t isSingleBits = 1;
        
        static constexpr size_t singleBranchBits = 16 - isSingleBits;
        static constexpr size_t maxSingleBranches = 1u << singleBranchBits;
        static constexpr size_t singleBranchBufferSize = minBytesForBits(maxSingleBranches);
        
        static constexpr size_t nonSingleBranchBits = 64 - isSingleBits;
        static constexpr size_t nonSingleBranchBufferSize = minBytesForBits(nonSingleBranchBits);
        
        static constexpr size_t minBufferSize = math::max(singleBranchBufferSize, nonSingleBranchBufferSize);
        
        static constexpr size_t numPages = 1; // for now
        static const size_t pageSize;
        static const size_t pageChunkSize;
        static const size_t bufferSize;
        
        union Counts {
            
            struct {
                u64 singleBranches;
                u64 multiBranches;
                u64 infiniteBranches;
            };
            std::array<u64, 3> all;
            
            void write(u8* out) const noexcept {
                std::copy(all.begin(), all.end(), out);
            }
            
        } count = {};
        
        struct Indices {
            
            u8 byteBit = 0;
            u16 chunkBit = 0;
            size_t byte = 0;
            size_t lastChunkByte = 0;
            
            constexpr u16 branchChunkBits() noexcept {
                // shift up and set first bit to 1 for isSingle
                return static_cast<u16>((chunkBit << 1) | 0b1);
            }
            
            void startNextBranchChunk() noexcept {
                lastChunkByte = byte;
            }
            
            constexpr bool isStartOfBranchChunk() noexcept {
                return byte == lastChunkByte;
            }
            
            void skipSingleBranchCount() noexcept {
//                if (isStartOfBranchChunk()) {
//                    byte += sizeof(chunkBit);
//                }
                // optimized (branchless) version of above
                byte += static_cast<size_t>(isStartOfBranchChunk()) * sizeof(chunkBit);
            }
            
            void nextBranchChunk() noexcept {
                startNextBranchChunk();
                chunkBit = 0;
                // byteBit = 0 should already be the case
            }
            
            void nextPageChunk() noexcept {
                // need to move all byte indices back by pageChunkSize
                // since buffer is moved ahead by pageChunkSize
                // lengths stay the same, and per byte bit counters aren't affected
                byte -= pageChunkSize;
                lastChunkByte -= pageChunkSize;
            }
            
        } index = {};
        
        /**
         * MMapOutput allows for high-throughput, zero-copy output.
         * Given a file descriptor fd, MMapOutput creates:
         *      fd: the given file descriptor
         *      start: a start mapping that holds the counts of each branch type (see Counts)
         *      offset: the current mmap offset, a multiple of the page size
         *      firstPageChunk: the first of two mmap'd page chunks (of length pageChunkSize)
         *      secondPageChunk: the second of two mmap'd page chunks (of length pageChunkSize)
         *      buffer: a pointer to both page chunks they're conscutive)
         *
         * nextPageChunk() moves the buffer to the next page chunk
         */
        class MMapOutput {
        
        private:
            
            static u8* mmap(int fd, size_t length, size_t offset = 0) {
                return fse::mmap(fd, PROT_WRITE, MAP_SHARED, length, offset);
            }
            
            static constexpr size_t startSize = sizeof(count.all);
            
            const int fd;
        
        public:
            
            u8* const start;
        
        private:
            
            size_t offset = 0;
            u8* firstPageChunk = nullptr;
            u8* secondPageChunk = nullptr;
        
        public:
            
            u8* buffer = nullptr; // = firstPageChunk, but accessible up to end of secondPageChunk
        
        private:
            
            void mmapSecondPageChunk() {
                secondPageChunk = mmap(fd, pageChunkSize, offset);
                offset += pageChunkSize;
            }
        
        public:
            
            explicit MMapOutput(int fd) : fd(fd), start(mmap(fd, startSize)) {
                mmapSecondPageChunk();
                firstPageChunk = secondPageChunk;
                mmapSecondPageChunk();
                buffer = firstPageChunk;
            }
            
            ~MMapOutput() {
                munmap(start, startSize);
                munmap(firstPageChunk, pageChunkSize);
                munmap(secondPageChunk, pageChunkSize);
            }
            
            void nextPageChunk() {
                munmap(firstPageChunk, pageChunkSize);
                firstPageChunk = secondPageChunk;
                mmapSecondPageChunk();
                buffer = firstPageChunk;
            }
            
            template <typename T>
            size_t write(size_t index, T value) {
                for (size_t i = 0; i < sizeof(T); i++) {
                    buffer[index + i] = static_cast<u8>(value >> (i * CHAR_BIT));
                }
                return index + sizeof(T);
            }
            
        } out;
    
    public:
        
        explicit BranchCoverageRuntime(int fd) : out(fd) {
            index.byte = count.all.size();
            index.startNextBranchChunk();
        }
    
    private:
        
        static int createOutput(const fs::path& file) {
            const int fd = creat(file.c_str(), 0644);
            if (fd == -1) {
                throw fs::filesystem_error(file.string(), std::error_code());
            }
            return fd;
        }
    
    public:
        
        explicit BranchCoverageRuntime(const fs::path& file)
                : BranchCoverageRuntime(createOutput(file)) {}
    
    private:
        
        void writeChunkLength() noexcept {
            out.write(index.lastChunkByte, index.branchChunkBits());
        }
        
        void writeCounts() noexcept {
            count.write(out.start);
        }
        
        void nextPageChunk() {
            const bool isPageChunkFull = index.byte == bufferSize;
            out.nextPageChunk();
            index.nextPageChunk();
            if (isPageChunkFull) {
                out.nextPageChunk();
                index.nextPageChunk();
            }
        }
        
        void nextBranchChunk() {
            writeChunkLength();
            nextPageChunk();
            index.nextBranchChunk();
            writeCounts(); // write on every branch chunk in case of crash
        }
        
        constexpr bool shouldMoveToNextPageChunk() noexcept {
            return index.byte >= pageChunkSize;
        }
        
        void tryNextPageChunk() {
            if (shouldMoveToNextPageChunk()) {
                nextPageChunk();
            }
        }
        
        constexpr bool shouldMoveToNextBranchChunk() noexcept {
            return index.byte == bufferSize && index.byteBit == 0;
        }
        
        void tryNextBranchChunk() {
            if (shouldMoveToNextBranchChunk()) {
                nextBranchChunk();
            }
        }
        
        void onNonSingleBranch(u64 value) {
            tryNextPageChunk();
            // out.buffer not necessarily 64-bit aligned
            index.byte = out.write(index.byte, value);
            tryNextPageChunk();
            index.startNextBranchChunk();
        }
    
    public:
        
        void onSingleBranch(bool value) {
            count.singleBranches++;
            index.skipSingleBranchCount();
            out.buffer[index.byte] |= 1 << index.byteBit;
            index.byteBit = index.byteBit & static_cast<u8>(8 - 1); // index.byteBit++ % 8
            if (index.byteBit == 1) {
                index.byte++; // keep things aligned
            }
            index.chunkBit++;
            tryNextBranchChunk();
        }
        
        void onMultiBranch(u32 branchNum, u32 numBranches) {
            count.multiBranches++;
            // first bit is isSingle = false
            // second bit is isMulti = true
            onNonSingleBranch(0b01 | branchNum << 1 | static_cast<u64>(numBranches) << (32 + 2));
        }
        
        void onInfiniteBranch(u64 address) {
            count.infiniteBranches++;
            // first bit is isSingle = false
            // second bit is isMulti = false
            onNonSingleBranch(0b00 | address << 2);
        }
        
    };
    
    const size_t BranchCoverageRuntime::pageSize = fse::pageSize;
    const size_t BranchCoverageRuntime::pageChunkSize = math::multipleGreaterThan(pageSize * numPages, minBufferSize);
    // 2 * minBufferSize so that if buffer more than half full, can move to the next page chunk
    const size_t BranchCoverageRuntime::bufferSize = 2 * pageChunkSize;
    
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
