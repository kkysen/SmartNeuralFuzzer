//
// Created by Khyber on 6/12/2019.
//

#include "src/share/io/LEB128Reader.h"

#include <iostream>

#include <unistd.h>

void parse(const fs::path& path, std::ostream& out) {
    io::LEB128Reader reader {io::ReadOnlyMappedMemory(path)};
    u64 last = 0;
    while (reader.hasNext()) {
        const auto delta = reader.next<i64>();
//        out << "delta: " << delta << '\n';
        const auto blockIndex = static_cast<u64>(last + delta);
        last = blockIndex;
        out << blockIndex << '\n';
    }
    out.flush();
}

int main() {
    parse("blocks.bin", std::cout);
}
