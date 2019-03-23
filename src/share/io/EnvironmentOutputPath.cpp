//
// Created by Khyber on 3/22/2019.
//

#include "src/share/io/EnvironmentOutputPath.h"

namespace env::path::output {
    
    fs::path get(DefaultOutputPath defaultOutputPath, const std::string& environmentVariableName) {
        const char* outputPath = std::getenv(environmentVariableName.c_str());
        if (outputPath) {
            return outputPath;
        } else {
            return defaultOutputPath(environmentVariableName, getpid());
        }
    }
    
}
