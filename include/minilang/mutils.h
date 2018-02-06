#pragma once

#include <string>
#include <sstream>
#include <minilang/mtype.h>

namespace mini {
    namespace utils {
        /**
         * Create indentation
         * @param val
         * @return spaces
         */
        inline std::string indent(int val) {
            std::stringstream indent;
            for(size_t i=0; i < val; i++) {
                indent << std::string(4, ' ');
            }
            return indent.str();
        }

        /**
         * Convert enum to minilang type
         * @param type
         * @return string
         */
        inline std::string toMiniType(mini::TYPE type) {
            switch (type) {
                case mini::TYPE::STRING:
                    return "string";
                case mini::TYPE::INTEGER:
                    return "int";
                case mini::TYPE::FLOAT:
                    return "float";
                case mini::TYPE::BOOLEAN:
                    return "boolean";
                default:
                    throw std::runtime_error("Cannot generate minilang code for an undefined type");
            }
        }

        /**
         * Convert enum to C type
         * @param type
         * @return string
         */
        inline std::string toCType(mini::TYPE type) {
            switch (type) {
                case mini::TYPE::STRING:
                    return "char*";
                case mini::TYPE::INTEGER:
                    return "int";
                case mini::TYPE::FLOAT:
                    return "float";
                case mini::TYPE::BOOLEAN:
                    return "bool";
                default:
                    throw std::runtime_error("Cannot generate C code for an undefined type");
            }
        }

        /**
         * Convert enum to C string format
         * @param type
         * @return string
         */
        inline std::string toCStringFormat(mini::TYPE type) {
            switch (type) {
                case mini::TYPE::STRING:
                    return "%s";
                case mini::TYPE::INTEGER:
                case mini::TYPE::BOOLEAN:
                    return "%d";
                case mini::TYPE::FLOAT:
                    return "%f";
                default:
                    throw std::runtime_error("Cannot get string format for an undefined type");
            }
        }
    }
}