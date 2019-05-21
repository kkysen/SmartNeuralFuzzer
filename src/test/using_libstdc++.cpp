//
// Created by Khyber on 5/20/2019.
//

#include <string>
#include <iostream>
#include <iterator>

int main(int argc, const char* const* argv) {
    std::copy(argv, argv + argc, std::ostream_iterator<const char*>(std::cout, "\n"));
}

