//
// Created by Khyber on 5/21/2019.
//

#include "src/share/io/Popen.h"

#include "src/share/io/fse.h"

#include <iostream> // TODO remove

namespace io {
    
    Popen::Popen(const char* command, const char* mode) : _file(popen(command, mode)) {
        if (!_file) {
            using namespace std::string_literals;
            fse::_throw(fse::error(""s + "command: '" + command + "', mode = '" + mode + "'"));
        }
        std::cerr << command << std::endl; // TODO remove
        std::cerr << WEXITSTATUS(system("touch world")) << std::endl;
    }
    
    Popen::Popen(const std::string& string, const char* mode) : Popen(string.c_str(), mode) {}
    
    Popen::~Popen() {
        if (_file) {
            std::cerr << WEXITSTATUS(pclose(_file)) << std::endl;
//            pclose(_file);
        }
    }
    
}
