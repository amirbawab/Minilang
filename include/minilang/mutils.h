#pragma once

namespace mini {
    namespace utils {
        inline char* indent(int val) {
            const size_t size = sizeof(char) * val * 4 + sizeof(char);
            char* str = (char*)malloc(size);
            for(size_t i=0; i < size; i++) {
                str[i] = ' ';
            }
            str[size-1] = '\0';
            return str;
        }
    }
}