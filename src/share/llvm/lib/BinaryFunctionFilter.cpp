//
// Created by Khyber on 5/20/2019.
//

#include "src/share/llvm/lib/BinaryFunctionFilter.h"

#include "src/share/io/Popen.h"
#include "src/share/io/Stat.h"
#include "src/share/llvm/lib/conversions.h"
#include "src/share/common/hardAssert.h"

#include "llvm/Support/FileSystem.h"

#include <fstream>

namespace {
    
    fs::path getCacheDir() {
        const auto dir = fs::temp_directory_path() / "BinaryFunctionFilter";
        fs::create_directories(dir);
        return dir;
    }
    
    void purgeCacheDir() {
        // I need to use llvm's fs API here instead of std::filesystem b/c std::filesystem isn't complete
        
        using namespace llvm::sys;
        using namespace llvm::sys::fs;
        
        const auto cacheDir = getCacheDir();
        const auto now = TimePoint<>::clock::now();
        std::error_code ec;
        for (auto it = directory_iterator(cacheDir.string(), ec);
             it != directory_iterator();
             it.increment(ec)) {
            if (ec) {
                fse::_throw(::fs::filesystem_error("directory_iterator failed", cacheDir, ec));
            }
            const auto& entry = *it;
            const auto statusOrErr = entry.status();
            if (!statusOrErr) {
                fse::_throw(::fs::filesystem_error("status failed", entry.path(), statusOrErr.getError()));
            }
            const auto status = *statusOrErr;
            if (status.type() != file_type::regular_file) {
                continue;
            }
            using namespace std::literals;
            const auto cacheAge = now - status.getLastModificationTime();
            constexpr auto maxAge = 24h;
            if (cacheAge > maxAge) {
                llvm::errs() << "purging old cache file: " << entry.path() << "\n";
                remove(entry.path());
            }
        }
    }
    
    std::string getCacheFileName(const fs::path& objectFilePath) {
        auto cacheFileName = fs::absolute(objectFilePath).string();
        std::replace(cacheFileName.begin(), cacheFileName.end(), fs::path::preferred_separator, '_');
        cacheFileName += ".llvm.nm.txt";
        return cacheFileName;
    }
    
    fs::path getCacheFilePath(const fs::path& objectFilePath) {
        return getCacheDir() / getCacheFileName(objectFilePath);
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
    
    // TODO maybe cache files once joined, since there's a lot of repetition b/w, but it might not matter at all
    
    size_t symbolsToFunctionNames(const fs::path& objectFilePath, const fs::path& cacheFilePath) {
        using namespace llvm::convert;
        bool lastLineEmpty = false;
        llvm::StringSet<> functionNameLines; // need to remove duplicates
        const bool someLines = io::Popen(getCommand(objectFilePath))
                .forEachLine([&functionNameLines, &lastLineEmpty](const auto& line) {
                    const auto functionName = symbolLineToFunctionName(line, lastLineEmpty);
                    if (!functionName.empty()) {
                        functionNameLines.insert(ref(functionName));
                    }
                });
        hardAssert(someLines);
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
    
    void BinaryFunctionFilter::addMappedCacheFile(io::ReadOnlyMappedMemory<char>&& mappedCacheFile) {
        const std::string_view view = {mappedCacheFile.view().data(), mappedCacheFile.view().size()};
        mappedCacheFiles.push_back(std::move(mappedCacheFile));
        // cache files are just function name on each line
        size_t i = 0;
        for (size_t j; (j = view.find('\n', i)) != StringRef::npos; i = j + 1) {
            add(view.substr(i, j - i));
        }
        if (i != view.size()) {
            // don't include empty last line if it's been added for some reason
            add(view.substr(i, view.size() - i));
        }
    }
    
    void BinaryFunctionFilter::add(const fs::path& objectFilePath) {
        const auto stat = io::Stat::file(objectFilePath);
        stat.check();
        const auto cacheFilePath = getCacheFilePath(objectFilePath);
        const auto cacheStat = io::Stat::file(cacheFilePath);
        const bool cacheHit = !cacheMiss(stat, cacheStat);
        const size_t cacheFileLength = cacheHit
                                       ? cacheStat.size()
                                       : symbolsToFunctionNames(objectFilePath, cacheFilePath);
        addMappedCacheFile(io::ReadOnlyMappedMemory<char>(cacheFilePath, cacheFileLength));
    }
    
    RunOnce<> BinaryFunctionFilter::purgeCache = ::purgeCacheDir;
    
}
