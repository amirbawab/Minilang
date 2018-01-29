#pragma once

#define CODE_ERROR 1
#define CODE_SUCESS 0

#include <string>

namespace mini {
    void error_exit(std::string message);
}