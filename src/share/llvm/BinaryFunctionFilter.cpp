//
// Created by Khyber on 5/20/2019.
//

#include "BinaryFunctionFilter.h"

#include "src/share/io/Popen.h"
#include "src/share/io/Stat.h"
#include "src/share/llvm/conversions.h"

#include <fstream>

namespace {
    
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
        return cacheStat.error == ENOENT || cacheStat.lastTime.modification < fileStat.lastTime.modification;
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
        using namespace llvm::convert;
        bool lastLineEmpty = false;
        llvm::StringSet<> functionNameLines; // need to remove duplicates
        io::Popen(getCommand(objectFilePath))
                .forEachLine([&functionNameLines, &lastLineEmpty](const auto& line) {
                    const auto functionName = symbolLineToFunctionName(line, lastLineEmpty);
                    if (!functionName.empty()) {
                        functionNameLines.insert(ref(functionName));
                    }
                });
        std::ofstream cacheFile(cacheFilePath);
        size_t length = 0;
        for (const auto& entry : functionNameLines) {
            auto line = view(entry.first());
            cacheFile << line;
            length += line.size();
        }
        return length;
    }
    
}

namespace llvm::pass {
    
    bool BinaryFunctionFilter::contains(StringRef functionName) const noexcept {
        return functionNames.find(functionName) != functionNames.end();
    }
    
    bool BinaryFunctionFilter::operator()(StringRef functionName) const noexcept {
        return contains(functionName);
    }
    
    bool BinaryFunctionFilter::contains(Function& function) const noexcept {
        return contains(convert::view(function.getName()));
    }
    
    bool BinaryFunctionFilter::operator()(Function& function) const noexcept {
        return contains(function);
    }
    
    void BinaryFunctionFilter::add(StringRef functionName) {
        functionNames.insert(functionName);
    }
    
    bool BinaryFunctionFilter::contains(std::string_view functionName) const noexcept {
        return contains(convert::ref(functionName));
    }
    
    bool BinaryFunctionFilter::operator()(std::string_view functionName) const noexcept {
        return contains(functionName);
    }
    
    void BinaryFunctionFilter::add(std::string_view functionName) {
        add(convert::ref(functionName));
    }
    
    void BinaryFunctionFilter::addMappedCacheFile(io::ReadOnlyMappedMemory&& mappedCacheFile) {
        const auto view = mappedCacheFile.view();
        mappedCacheFiles.push_back(std::move(mappedCacheFile));
        // cache files are just function name on each line
        size_t i = 0;
        for (size_t j; (j = view.find('\n', i)) != StringRef::npos; i = j + 1) {
            add(view.substr(i, j));
        }
        if (i != view.size()) {
            // don't include empty last line if it's been added for some reason
            add(view.substr(i, view.size()));
        }
    }
    
    void BinaryFunctionFilter::add(const fs::path& objectFilePath) {
        const auto stat = io::Stat::file(objectFilePath);
        stat.check();
        const auto cacheFilePath = getCacheFilePath(objectFilePath);
        const auto cacheStat = io::Stat::file(cacheFilePath);
        const size_t cacheFileLength = cacheMiss(stat, cacheStat)
                                       ? symbolsToFunctionNames(objectFilePath, cacheFilePath)
                                       : cacheStat.size();
        addMappedCacheFile(io::ReadOnlyMappedMemory(cacheFilePath, cacheFileLength));
    }
    
}
