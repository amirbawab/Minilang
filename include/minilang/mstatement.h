#pragma once

#include <string>

namespace mini {
    class MStatement {
    public:
        virtual ~MStatement(){}

        /**
         * Prettify statement code
         * @param indent
         * @return pretty code
         */
        virtual std::string prettify(int indent) = 0;

        /**
         * Generate C code
         * @param indent
         * @return c code
         */
        virtual std::string toC(int indent) = 0;

        /**
         * Check type
         */
        virtual void typeCheck() = 0;
    };
}