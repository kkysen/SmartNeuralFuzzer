//
// Created by Khyber on 4/7/2019.
//

#include "src/main/runtime/coverage/CoverageOutput.h"

namespace runtime::coverage {
    
    RuntimeOutput output() {
        return RuntimeOutput("coverage");
    }
    
    io::Writer writer(const fse::Dir& dir, const std::string& name) {
        return io::Writer(dir.file(name + ".bin", O_WRONLY | O_CREAT | O_TRUNC, 0644));
    }
    
}
