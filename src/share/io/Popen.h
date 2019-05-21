//
// Created by Khyber on 5/21/2019.
//

#pragma once

#include <cstdio>
#include <string>
#include "src/share/stde/getline.h"

namespace io {
    
    class Popen {
    
    private:
        
        FILE* _file;
    
    public:
        
        static constexpr auto defaultMode = "r";
        
        constexpr FILE& file() const noexcept {
            return *_file;
        }
        
        explicit Popen(const char* command, const char* mode = defaultMode);
        
        explicit Popen(const std::string& string, const char* mode = defaultMode);
        
        ~Popen();
        
        Popen(const Popen& other) = delete;
        
        constexpr Popen(Popen&& other) noexcept : _file(other._file) {
            other._file = nullptr;
        }
        
        template <class F>
        void forEachLine(F f, char delimiter = '\n') {
            stde::forEachLine(f, file(), delimiter);
        }
        
    };
    
}
