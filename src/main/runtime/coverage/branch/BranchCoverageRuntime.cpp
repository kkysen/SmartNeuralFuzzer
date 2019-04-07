//
// Created by Khyber on 3/14/2019.
//

#include "BranchCoverageRuntime.h"

#include "src/share/common/lazy.h"
#include "src/share/io/WriteBuffer.h"
#include "src/share/io/EnvironmentOutputPath.h"

#include <numeric>
#include <sys/stat.h>

namespace runtime::coverage::branch {
    
    class BranchCoverageRuntime {
    
    private:
        
        static constexpr size_t pageSize = fse::page::constSize;
        
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
            
            const io::Writer write;
        
        public:
            
            explicit constexpr Counts(io::Writer&& write) noexcept : all({}), write(std::move(write)) {}
            
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
//            static constexpr Size bufferBitSize = bufferByteSize * numBits<u8>();
            
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
            
            const io::Writer write;
            
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
                writeBuffer(math::minBytesForBits(bitIndex));
                const u8 bitsInLastBytes = byteBitIndex();
                write(&bitsInLastBytes, sizeof(bitsInLastBytes));
            }
        
        public:
            
            explicit constexpr SingleBranches(io::Writer&& write) noexcept : write(std::move(write)) {}
            
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
            
            io::WriteBuffer<Record> buffer;
            
            void onRecord(Record record) noexcept {
                buffer.on(record);
            }
        
        public:
            
            explicit constexpr NonSingleBranches(io::Writer&& write) noexcept : buffer(std::move(write)) {}
            
            NonSingleBranches(const NonSingleBranches& other) = delete;
            
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
    
        Counts count;
        
        struct Branches {
            
            SingleBranches single;
            NonSingleBranches nonSingle;
            
            constexpr Branches(io::Writer&& singleWrite, io::Writer&& nonSingleWrite) noexcept
                    : single(std::move(singleWrite)), nonSingle(std::move(nonSingleWrite)) {}
            
        } branches;
    
    public:
        
        class Output {
        
        private:
            
            const fs::path& dirPath;
            const int dir;
            
            int createDir() noexcept(false) {
                if (mkdir(dirPath.c_str(), 0755) == -1 && errno != EEXIST) {
                    throw fse::error("mkdir", dirPath);
                }
                const int fd = open(dirPath.c_str(), O_DIRECTORY | O_PATH);
                if (fd == -1) {
                    throw fse::error("open(O_DIRECTORY | O_PATH)", dirPath);
                }
                return fd;
            }
            
            int createAtDir(const std::string& fileBaseName) noexcept(false) {
                const auto fileName = fileBaseName + ".bin";
                const int fd = openat(dir, fileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    throw fse::error("openat", dirPath, fileName);
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
                : count(io::Writer(writes.count)),
                  branches(io::Writer(writes.branches.single), io::Writer(writes.branches.nonSingle)) {}
        
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
        
        static constexpr auto getOutputDir = env::path::output::getter(
                [](const auto& var, auto pid) -> fs::path { return var + "." + std::to_string(pid) + ".dir"; });
    
    public:
        
        explicit BranchCoverageRuntime(const std::string& environmentVariableName = "coverage.branch.out")
                : BranchCoverageRuntime(getOutputDir(environmentVariableName)) {}
        
        static const LazilyConstructed<BranchCoverageRuntime> instance;
        
    };
    
    const LazilyConstructed<BranchCoverageRuntime> BranchCoverageRuntime::instance;
    
    auto& rt = BranchCoverageRuntime::instance;
    
}

using runtime::coverage::branch::rt;

API_BranchCoverage(onSingleBranch)(bool value) {
//    printf("BranchCoverage: onBranch: %s\n", value ? "true" : "false");
    rt().onSingleBranch(value);
}

API_BranchCoverage(onMultiBranch)(u32 branchNum, u32 numBranches) {
//    printf("BranchCoverage: onMultiBranch: %d/%d\n", branchNum, numBranches);
    rt().onMultiBranch(branchNum, numBranches);
}

API_BranchCoverage(onInfiniteBranch)(void* address) {
//    printf("BranchCoverage: onInfiniteBranch: %p\n", address);
    rt().onInfiniteBranch(address);
}
