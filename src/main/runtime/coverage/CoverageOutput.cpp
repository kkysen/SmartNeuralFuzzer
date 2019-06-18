//
// Created by Khyber on 4/7/2019.
//

#include "src/main/runtime/coverage/CoverageOutput.h"

namespace runtime::coverage {
    
    RuntimeOutput output() {
        return RuntimeOutput("coverage");
    }
    
    io::Writer writer(const fse::Dir& dir, const std::string& name) noexcept(false) {
        // O_CLOEXEC is so the files all close on exec(), after which our runtime will be gone
        // the exec hooks should handle all this anyway,
        // but it's safer to have the kernel handle it also
        return io::Writer(dir.file(name + ".bin", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644));
    }
    
}
