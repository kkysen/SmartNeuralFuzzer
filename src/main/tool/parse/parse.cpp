//
// Created by Khyber on 6/12/2019.
//

#include "src/share/io/DeltaReader.h"

#include <iostream>

#include <unistd.h>

void parse(const fs::path& path, std::ostream& out) {
    io::DeltaReader reader {io::ReadOnlyMappedMemory(path)};
    while (reader.hasNext()) {
        const auto blockIndex = reader.next();
        out << blockIndex << '\n';
    }
    out.flush();
}

int main(int, const char* const* argv) {
    parse(argv[1], std::cout);
}
