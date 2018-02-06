#pragma once

#include <string>

namespace mini {
    class MStatement {
    public:

        /**
         * Prettify statement code
         * @param indent
         * @return pretty code
         */
        virtual std::string prettify(int indent) = 0;
    };
}