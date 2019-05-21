//
// Created by Khyber on 5/20/2019.
//

#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

namespace hello {
    
    void transform(char* s) {
        std::string t = s;
        std::transform(t.begin(), t.end(), s, [](char c) -> char {
            return toupper(c);
        });
    }
    
}

int main(int argc, char** argv) {
    std::transform(argv, argv + argc, std::ostream_iterator<const char*>(std::cout, "\n"), [](char* s) {
        hello::transform(s);
        return s;
    });
//    std::copy(argv, argv + argc, std::ostream_iterator<const char*>(std::cout, "\n"));
}

//