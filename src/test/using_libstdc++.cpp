//
// Created by Khyber on 5/20/2019.
//

#include <string>
#include <iostream>

int main(int argc, const char* const* argv) {
    std::string s;
    for (auto i = 0; i < argc; i++) {
        s += argv[i];
    }
    std::cout << s;
    std::cout << std::endl;
}
