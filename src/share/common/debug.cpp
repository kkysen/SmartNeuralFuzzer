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
    
    Indentation indentation;
    
    const char* ErrorInfo::strerror(int errorNum) {
        return ::strerror(errorNum);
    }
    
    ErrorInfo::ErrorInfo(Info info) noexcept : ErrorInfo(info, errno, strerror) {}
    
}

std::ostream& operator<<(std::ostream& out, bool boolean) {
    return out << (boolean ? "true" : "false");
}
