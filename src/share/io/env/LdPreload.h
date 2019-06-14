//
// Created by Khyber on 6/10/2019.
//

#pragma once

#include <set>

namespace env::path {
    
    class LdPreload {

    public:
        
        static constexpr auto name = "LD_PRELOAD";
        static constexpr char delimiter = ':';

    private:
        
        size_t _size = 0;
        std::set<std::string_view> paths = {};
        
        mutable std::string buffer;

    public:
        
        constexpr size_t size() const noexcept {
            return _size;
        }
        
        void load();
        
        void store() const;
        
        bool add(std::string_view path);
        
        bool remove(std::string_view path);
        
        LdPreload& operator+=(std::string_view path);
        
        LdPreload& operator-=(std::string_view path);
        
    };
    
}
