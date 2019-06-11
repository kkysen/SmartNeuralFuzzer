//
// Created by Khyber on 5/20/2019.
//

#pragma once

#include <cstdio>
#include <string>

namespace stde {
    
    template <class F>
    bool forEachLine(F f, FILE& file, char delimiter = '\n') {
        bool someLines = false;
        char* line = nullptr;
        ssize_t length;
        size_t n;
        while ((length = ::getdelim(&line, &n, delimiter, &file)) != -1) {
            someLines = true;
            f(std::string_view(line, static_cast<size_t>(length)));
        }
        free(line);
        return someLines;
    }
    
}
