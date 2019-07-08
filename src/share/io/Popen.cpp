//
// Created by Khyber on 5/21/2019.
//

#include "src/share/io/Popen.h"

#include "src/share/io/fse.h"

#include <sstream>

//#include <iostream> // TODO remove

namespace io {
    
    Popen::Popen(const char* command, const char* mode) : _file(::popen(command, mode)) {
        if (!_file) {
            using namespace std::string_literals;
            fse::_throw(fse::error(""s + "command: '" + command + "', mode = '" + mode + "'"));
        }
//        std::cout << command << std::endl;
    }
    
    Popen::Popen(const std::string& string, const char* mode) : Popen(string.c_str(), mode) {}
    
    void Popen::close() noexcept {
        if (const auto file = _file.exchange(nullptr)) {
            ::pclose(file);
        }
    }
    
    Popen::~Popen() {
        close();
    }
    
    std::string Popen::read() {
        std::ostringstream ss;
        char buffer[fse::page::size::io::dynamic];
        size_t n;
        do {
            n = ::fread(buffer, 1, sizeof(buffer), _file);
            ss.write(buffer, n);
        } while (n == sizeof(buffer));
        return ss.str();
    }
    
}
