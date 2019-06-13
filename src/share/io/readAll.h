//
// Created by Khyber on 6/13/2019.
//

#pragma once

#include <string>

namespace io {
    
    std::string readAll(int fd);
    
    std::string readAll(const char* path);
    
    template <class String>
    std::string readAll(const String& string) {
        return readAll(string.c_str());
    }
    
}
