//
// Created by Khyber on 3/22/2019.
//

#include "src/share/common/debug.h"

namespace debug {
    
    bool mode = true;
    
    std::ostream* out = &std::cout;
    
    bool reversed = false;
    
    char Indentation::defaultChar = ' ';
    size_t Indentation::defaultIndent = 4;
    
    void Indentation::syncString() {
        string.resize(_size, defaultChar);
    }
    
    Indentation::Indentation(size_t size) noexcept
            : _size(size), string() {}
    
    void Indentation::indent(size_t indent) {
        _size += indent;
        syncString();
    }
    
    void Indentation::unIndent(size_t indent) {
        if (_size < indent) {
            _size = 0;
        } else {
            _size -= indent;
        }
        syncString();
    }
    
    Indentation indentation;
    
    const char* ErrorInfo::strerror(int errorNum) {
        return ::strerror(errorNum);
    }
    
    ErrorInfo::ErrorInfo(Info info) noexcept : ErrorInfo(info, errno, strerror) {}
    
    Indented::Indented(Indentation& indentation) : indentation(indentation) {
        indentation.indent();
    }
    
    Indented::~Indented() {
        indentation.unIndent();
    }
    
}

namespace {
    
    const auto& unused1 = std::cout << std::boolalpha;
    const auto& unused2 = std::cerr << std::boolalpha;
    
}
