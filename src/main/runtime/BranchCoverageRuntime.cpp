//
// Created by Khyber on 3/14/2019.
//

#include "BranchCoverageRuntime.h"

#include "src/share/common/math.h"
#include "src/share/common/fs.h"
#include "src/share/common/fse.h"

#include <algorithm>
#include <numeric>
#include <src/share/common/lazy.h>
#include <sys/stat.h>

namespace {
    
    // can't have constexpr statics based on static constexpr functions in same class
    // so have to define them at the file level
    
    constexpr size_t minBytesForBits(size_t bits) noexcept {
        return math::divUp(bits, numBits<u8>());
    }
    
    class BranchCoverageRuntime {
    
    private:
        
        static constexpr size_t pageSize = 4096; // only usually correct, but I need it as a constexpr
        
        class Write {
        
        public:
            
            int fd;
            
            constexpr bool isValid() noexcept {
                return fd >= 0;
            }
            
            explicit constexpr Write(int fd) : fd(fd) {}
            
            constexpr Write(Write&& other) noexcept : Write(other.fd) {
                other.fd = -1; // don't close(fd) early
            }
            
            Write(const Write& other) = delete;
            
            ~Write() noexcept {
                if (isValid()) {
                    close(fd);
                }
            }
            
            void operator()(const void* bytes, size_t numBytes) const noexcept {
                ::write(fd, bytes, numBytes);
            }
            
            void absolute(const void* bytes, size_t numBytes, size_t offset = 0) const noexcept {
                ::pwrite(fd, bytes, numBytes, offset);
            }
            
        };
        
        class Counts {
        
        public:
            
            union {
                
                struct {
                    u64 single;
                    u64 multi;
                    u64 infinite;
                } branches = {};
                
                std::array<u64, 3> all;
                
            };
        
        private:
            
            const Write write;
        
        public:
            
            explicit constexpr Counts(Write&& write) noexcept : write(std::move(write)), all({}) {}
            
            Counts(const Counts& other) = delete;
            
            ~Counts() noexcept {
                flush();
            }
            
            void flush() const noexcept {
                write.absolute(all.data(), sizeof(all));
            }
            
        };
        
        class SingleBranches {
        
        private:
            
            using Size = u32;
            using Chunk = u64;
            
            static constexpr Size bufferByteSize = static_cast<Size>(math::lcm(pageSize, sizeof(Chunk)));
            static constexpr Size bufferSize = bufferByteSize / sizeof(Chunk);
            static constexpr Size bufferBitSize = bufferByteSize * numBits<u8>();
            
            std::array<Chunk, bufferSize> buffer = {};
            Size bitIndex = 0;
            Size bitIndexDiff = 0;
            
            struct shift {
                
                static constexpr Size byte = 3;
                static_assert(1 << byte == numBits<u8>());
                
                static constexpr Size chunk = 6;
                static_assert(1 << chunk == numBits<Chunk>());
                
            };
            
            constexpr Size byteIndex() const noexcept {
                return bitIndex >> shift::byte;
            }
            
            constexpr Size chunkIndex() const noexcept {
                return bitIndex >> shift::chunk;
            }
            
            constexpr u8 byteBitIndex() const noexcept {
                return static_cast<u8>(bitIndex & ((1 << shift::byte) - 1));
            }
            
            constexpr u8 chunkBitIndex() const noexcept {
                return static_cast<u8>(bitIndex & ((1 << shift::chunk) - 1));
            }
        
        public:
            
            Size resetBitIndexDiff() noexcept {
                const auto temp = bitIndexDiff;
                bitIndexDiff = 0;
                return temp;
            }
        
        private:
            
            const Write write;
            
            void writeBuffer(size_t numBytes = sizeof(buffer)) noexcept {
                write(buffer.begin(), numBytes);
            }
            
            void flush() noexcept {
                writeBuffer();
                bitIndex = 0;
            }
            
            constexpr bool shouldFlush() const noexcept {
                return chunkIndex() == buffer.size();
            }
            
            void tryFlush() noexcept {
                if (shouldFlush()) {
                    flush();
                }
            }
            
            void finalFlush() noexcept {
                writeBuffer(minBytesForBits(bitIndex));
                const u8 bitsInLastBytes = byteBitIndex();
                write(&bitsInLastBytes, sizeof(bitsInLastBytes));
            }
        
        public:
            
            explicit constexpr SingleBranches(Write&& write) noexcept : write(std::move(write)) {}
            
            SingleBranches(const SingleBranches& other) = delete;
            
            ~SingleBranches() noexcept {
                finalFlush();
            }
            
            void on(bool value) noexcept {
                buffer[chunkIndex()] |= static_cast<u64>(value) << chunkBitIndex();
                bitIndex++;
                bitIndexDiff++;
                tryFlush();
            }
            
        };
        
        class NonSingleBranches {
        
        private:
            
            struct Record {
                u32 bitIndexDiff: 31, isMultiple: 1;
                u32 low;
                u32 high;
            };
            
            static constexpr size_t bufferByteSize = math::lcm(pageSize, sizeof(Record));
            static constexpr size_t bufferSize = bufferByteSize / sizeof(Record);
            
            std::array<Record, bufferSize> buffer = {};
            size_t index = 0;
            
            const Write write;
            
            void writeBuffer(size_t numBytes = sizeof(buffer)) noexcept {
                write(buffer.begin(), numBytes);
            }
            
            void flush() noexcept {
                writeBuffer();
                index = 0;
            }
            
            constexpr bool shouldFlush() noexcept {
                return index == buffer.size();
            }
            
            void tryFlush() noexcept {
                if (shouldFlush()) {
                    flush();
                }
            }
            
            void finalFlush() noexcept {
                writeBuffer(index * sizeof(Record));
            }
            
            void onRecord(Record record) noexcept {
                buffer[index++] = record;
                tryFlush();
            }
        
        public:
            
            explicit constexpr NonSingleBranches(Write&& write) noexcept : write(std::move(write)) {}
            
            NonSingleBranches(const NonSingleBranches& other) = delete;
            
            ~NonSingleBranches() noexcept {
                finalFlush();
            }
            
            void onMulti(u32 branchNum, u32 numBranches, u32 bitIndexDiff) noexcept {
                onRecord({
                                 .bitIndexDiff = bitIndexDiff,
                                 .isMultiple = static_cast<u32>(true),
                                 .low = branchNum,
                                 .high = numBranches,
                         });
            }
            
            void onInfinite(u64 address, u32 bitIndexDiff) noexcept {
                onRecord({
                                 .bitIndexDiff = bitIndexDiff,
                                 .isMultiple = static_cast<u32>(false),
                                 .low = static_cast<u32>(address),
                                 .high = static_cast<u32>(address >> 32),
                         });
            }
            
        };
        
        struct Branches {
            
            SingleBranches single;
            NonSingleBranches nonSingle;
            
            constexpr Branches(Write&& singleWrite, Write&& nonSingleWrite) noexcept
                    : single(std::move(singleWrite)), nonSingle(std::move(nonSingleWrite)) {}
            
        } branches;
        
        Counts count;
        
        class Output {
        
        private:
            
            const fs::path& dirPath;
            const int dir;
            
            void error(const std::string& filePath) noexcept(false) {
                throw fs::filesystem_error(filePath, std::error_code());
            }
            
            int createDir() noexcept(false) {
                if (mkdir(dirPath.c_str(), 0755) == -1 && errno != EEXIST) {
                    error(dirPath);
                }
                const int fd = open(dirPath.c_str(), O_DIRECTORY | O_PATH);
                if (fd == -1) {
                    perror("createDir:open");
                    error(dirPath);
                }
                return fd;
            }
            
            int createAtDir(const std::string& fileName) noexcept(false) {
                const int fd = openat(dir, fileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    error(dirPath / fileName);
                }
                return fd;
            }
        
        public:
            
            const int count;
            const struct {
                const int single;
                const int nonSingle;
            } branches;
            
            explicit Output(const fs::path& dirPath) noexcept(false)
                    : dirPath(dirPath),
                      dir(createDir()),
                      count(createAtDir("counts")),
                      branches({.single = createAtDir("single"), .nonSingle = createAtDir("nonSingle")}) {}
            
            ~Output() {
                close(dir);
            }
            
        };
        
        explicit BranchCoverageRuntime(Output&& writes) noexcept
                : count(Write(writes.count)),
                  branches(Write(writes.branches.single), Write(writes.branches.nonSingle)) {}
    
    public:
        
        explicit BranchCoverageRuntime(const fs::path& directoryPath) noexcept(false)
                : BranchCoverageRuntime(Output(directoryPath)) {}
        
        void onSingleBranch(bool value) noexcept {
            count.branches.single++;
            branches.single.on(value);
        }
        
        void onMultiBranch(u32 branchNum, u32 numBranches) noexcept {
            count.branches.multi++;
            branches.nonSingle.onMulti(branchNum, numBranches, branches.single.resetBitIndexDiff());
            count.flush();
        }
        
        void onInfiniteBranch(void* address) noexcept {
            count.branches.infinite++;
            branches.nonSingle.onInfinite(reinterpret_cast<u64>(address), branches.single.resetBitIndexDiff());
            count.flush();
        }
    
    private:
        
        static std::string defaultOutputDir(const std::string& environmentVariableName) {
            return environmentVariableName + "." + std::to_string(getpid()) + "." + "dir";
        }
        
        static fs::path getOutputDirFromEnvironment(const std::string& environmentVariableName) {
            const char* outputPath = std::getenv(environmentVariableName.c_str());
            if (outputPath) {
                return outputPath;
            } else {
                return defaultOutputDir(environmentVariableName);
            }
        }
    
    public:
        
        explicit BranchCoverageRuntime(const std::string& environmentVariableName = "coverage.branch.out")
                : BranchCoverageRuntime(getOutputDirFromEnvironment(environmentVariableName)) {}
        
        static const LazilyConstructed<BranchCoverageRuntime> instance;
        
    };
    
    const LazilyConstructed<BranchCoverageRuntime> BranchCoverageRuntime::instance;
    
    auto& runtime = BranchCoverageRuntime::instance;
    
}

API_BranchCoverage(onSingleBranch)(bool value) {
//    printf("BranchCoverage: onBranch: %s\n", value ? "true" : "false");
    runtime().onSingleBranch(value);
}

API_BranchCoverage(onMultiBranch)(u32 branchNum, u32 numBranches) {
//    printf("BranchCoverage: onMultiBranch: %d/%d\n", branchNum, numBranches);
    runtime().onMultiBranch(branchNum, numBranches);
}

API_BranchCoverage(onInfiniteBranch)(void* address) {
//    printf("BranchCoverage: onInfiniteBranch: %p\n", address);
    runtime().onInfiniteBranch(address);
}
