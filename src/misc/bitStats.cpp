//
// Created by Khyber on 6/17/2019.
//

#include "src/share/io/readAll.h"
#include "src/share/common/numbers.h"

#include "src/share/lib/corrade/CorradeArrayView.h"

#include <iostream>

using namespace Corrade::Containers;

void run(const char* path) {
    size_t n[2] = {};
    std::string_view names[2] = {"true", "false"};
    
    bool last = false;
    size_t streakLength = 0;
    
    std::string s = io::readAll(path);
    std::cout << "numBits: " << s.size() * CHAR_BIT << std::endl;
    
    using Word = u8;
    const ArrayView<const Word> words = {reinterpret_cast<const Word*>(s.data()), s.size() * sizeof(s[0]) / sizeof(words[0])};
    for (const auto word : words) {
        for (size_t i = 0; i < sizeof(word) * CHAR_BIT; i++) {
            const bool b = (word & (1u << i) >> i);
            n[b]++;
            const bool streak = last == b;
            if (streak) {
                streakLength++;
            } else {
                if ((streakLength & (8u - 1u)) != 0) {
                    std::cout << "streak: " << names[last] << ": " << streakLength << "\n";
                }
                streakLength = 1;
            }
//            std::cout << names[b] << std::endl;
            last = b;
        }
    }
    std::cout << "streak: " << names[last] << ": " << streakLength << "\n";
    
    for (size_t i = 0; i < 2; i++) {
        std::cout << names[i] << ": " << n[i] << std::endl;
    }
}

int main(int, char** argv) {
    run(argv[1]);
}
