#include <minilang/mreport.h>
#include <iostream>

void mini::error_exit(std::string message) {
    std::cerr << "Error: " << message << std::endl;
    exit(CODE_ERROR);
}