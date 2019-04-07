//
// Created by Khyber on 4/7/2019.
//

#pragma once

#include "src/main/runtime/RuntimeOutput.h"
#include "src/share/io/Writer.h"

namespace runtime::coverage {
    
    RuntimeOutput output();
    
    io::Writer writer(const fse::Dir& dir, const std::string& name);
    
}

