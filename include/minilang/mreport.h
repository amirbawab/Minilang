#pragma once

#define CODE_ERROR 1
#define CODE_SUCESS 0

#include <string>
#include <iostream>

extern std::string e_fileName;

namespace mini {
    namespace report {
        inline void error_exit(std::string message, int line) {
            std::cerr << "Error: " << message << " at line " << line << " in file: " << e_fileName << std::endl;
            exit(CODE_ERROR);
        }
    }
}