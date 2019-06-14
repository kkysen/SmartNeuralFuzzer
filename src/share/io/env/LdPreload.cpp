//
// Created by Khyber on 6/10/2019.
//

#include "src/share/io/env/LdPreload.h"

#include "src/share/stde/split.h"

namespace env::path {
    
    void LdPreload::load() {
        const std::string_view raw = ::getenv(name);
        _size = raw.size();
        paths.clear();
        stde::split(raw, delimiter, [this](auto path) {
            paths.emplace(path);
        });
    }
    
    void LdPreload::store() const {
        buffer.clear();
        buffer.reserve(_size + 1);
        for (const auto& path : paths) {
            buffer += path;
            buffer += delimiter;
        }
        buffer.pop_back();
        ::setenv(name, buffer.c_str(), true);
    }
    
    bool LdPreload::add(std::string_view path) {
        const bool added = paths.emplace(path).second;
        if (added) {
            _size += path.size() + 1;
        }
        return added;
    }
    
    bool LdPreload::remove(std::string_view path) {
        const bool removed = paths.erase(path) > 0;
        if (removed) {
            if (paths.empty()) {
                _size = 0;
            } else {
                _size -= path.size() + 1;
            }
        }
        return removed;
    }
    
    LdPreload& LdPreload::operator+=(std::string_view path) {
        add(path);
        return *this;
    }
    
    LdPreload& LdPreload::operator-=(std::string_view path) {
        remove(path);
        return *this;
    }
    
}
