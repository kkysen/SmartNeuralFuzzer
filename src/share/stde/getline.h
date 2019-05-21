//
// Created by Khyber on 5/20/2019.
//

#pragma once

#include <cstdio>
#include <string>

namespace stde {
    
    template <class F>
    void forEachLine(F f, FILE& file, char delimiter = '\n') {
        char* line = nullptr;
        ssize_t length;
        size_t n;
        while ((length = ::getdelim(&line, &n, delimiter, &file)) != -1) {
            f(std::string_view(line, static_cast<size_t>(length)));
        }
        free(line);
    }
    
}
