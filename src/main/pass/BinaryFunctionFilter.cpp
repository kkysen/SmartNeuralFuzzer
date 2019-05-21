//
// Created by Khyber on 5/20/2019.
//

#include "BinaryFunctionFilter.h"

#include <fstream>
#include <src/share/io/fse.h>
#include <src/share/io/Stat.h>
#include <src/share/stde/getline.h>
#include <src/share/llvm/debug.h>

namespace {
    
    using StringRef = llvm::pass::BinaryFunctionFilter::StringRef;
    
//    auto& errs() {
//        return std::cout;
//    }
    
    #define dbg _dbg
    
    std::string getCacheFileName(const fs::path& objectFilePath) {
        auto cacheFileName = fs::absolute(objectFilePath).string();
        std::replace(cacheFileName.begin(), cacheFileName.end(), fs::path::preferred_separator, '_');
        cacheFileName += ".llvm.nm.txt";
        return cacheFileName;
    }
    
    fs::path getCacheFilePath(const fs::path& objectFilePath) {
        fs::path cacheDir = fs::temp_directory_path() / "BinaryFunctionFilter";
        fs::create_directories(cacheDir);
        return cacheDir / getCacheFileName(objectFilePath);
    }
    
    std::string getCommand(const fs::path& objectFilePath) {
        return "llvm-nm --defined-only -format=bsd -no-sort " + objectFilePath.string();
    }
    
    constexpr bool cacheMiss(const io::Stat& fileStat, const io::Stat& cacheStat) noexcept {
        return cacheStat.error == ENOENT || fileStat.lastTime.modification < cacheStat.lastTime.modification;
    }
    
    // get pure function name from whole symbol line
    // empty return string means skip it
    // only keep
    constexpr std::string_view symbolLineToFunctionName(std::string_view line, bool& lastLineEmpty) noexcept {
        if (lastLineEmpty) {
            lastLineEmpty = false;
            return "";
        }
        if (line.empty()) {
            lastLineEmpty = true;
            return "";
        }
        // line format is "---------------- <typeCode> <functionName>\n"
        const size_t i = line.find(' ');
        const char typeCode = line[i + 1];
        switch (typeCode) {
            case 'C': // common: multiple defs into 1
            case 'W': // weak: multiple defs into 0 or 1
            case 't': // local function
            case 'T': // global function
                return line.substr(i + 3);
            default:
                return "";
        }
    }
    
    size_t symbolsToFunctionNames(const fs::path& objectFilePath, const fs::path& cacheFilePath) {
        std::ofstream cacheFile(cacheFilePath);
        const auto command = getCommand(objectFilePath);
        dbg(command);
        FILE& file = *popen(command.c_str(), "r"); // NOLINT(cert-fio38-c,misc-non-copyable-objects)
        size_t length = 0;
        bool lastLineEmpty = false;
        stde::forEachLine([&cacheFile, &length, &lastLineEmpty](const auto& line) {
//            errs() << line;
            const auto functionName = symbolLineToFunctionName(line, lastLineEmpty);
            if (!functionName.empty()) {
//                errs() << functionName;
                cacheFile << functionName;
                length += functionName.size();
            }
        }, file);
        pclose(&file);
        return length;
    }
    
    StringRef mapCacheFile(const fs::path& cacheFilePath, size_t fileLength) {
        const int fd = ::open(cacheFilePath.c_str(), O_RDONLY);
        const char* data = fse::mmap<const char>(fd, PROT_READ, MAP_PRIVATE, fileLength);
        close(fd);
        return StringRef(data, fileLength);
    }
    
}

namespace llvm::pass {
    
//    using ::errs;
    
    bool BinaryFunctionFilter::contains(StringRef functionName) const noexcept {
        return functionNames.find(functionName) != functionNames.end();
    }
    
    bool BinaryFunctionFilter::operator()(StringRef functionName) const noexcept {
        return contains(functionName);
    }
    
//    bool BinaryFunctionFilter::contains(Function& function) const noexcept {
//        return contains(function.getName());
//    }
//
//    bool BinaryFunctionFilter::operator()(Function& function) const noexcept {
//        return contains(function);
//    }
    
    void BinaryFunctionFilter::add(StringRef functionName) {
//        errs() << "BinaryFunctionFilter: " << functionName << "\n";
        functionNames.insert(functionName);
    }
    
    void BinaryFunctionFilter::addMappedCacheFile(StringRef mappedCacheFile) {
        // cache files are just function name on each line
        dbg("");
        size_t i = 0;
        for (size_t j; (j = mappedCacheFile.find('\n', i)) != StringRef::npos; i = j + 1) {
            add(mappedCacheFile.substr(i, j));
//            add(mappedCacheFile.slice(i, j));
        }
        if (i != mappedCacheFile.size()) {
            // don't include empty last line if it's been added for some reason
            add(mappedCacheFile.substr(i, mappedCacheFile.size()));
//            add(mappedCacheFile.slice(i, mappedCacheFile.size()));
        }
    }
    
    void BinaryFunctionFilter::add(const fs::path& objectFilePath) {
        dbg(objectFilePath);
        const auto stat = io::Stat::file(objectFilePath);
        dbg(stat.error);
        stat.check();
        const auto cacheFilePath = getCacheFilePath(objectFilePath);
        dbg(cacheFilePath);
        const auto cacheStat = io::Stat::file(cacheFilePath);
        const bool skipCache = cacheMiss(stat, cacheStat);
        dbg(skipCache ? "true" : "false");
        const size_t cacheFileLength = skipCache
                                       ? symbolsToFunctionNames(objectFilePath, cacheFilePath)
                                       : cacheStat.size;
        addMappedCacheFile(mapCacheFile(cacheFilePath, cacheFileLength));
    }
    
    BinaryFunctionFilter::~BinaryFunctionFilter() {
        errs() << functionNames.size() << "\n";
        for (auto mappedCacheFile : mappedCacheFiles) {
            const void* data = mappedCacheFile.data();
            ::munmap(const_cast<void*>(data), mappedCacheFile.size());
        }
    }
    
}
