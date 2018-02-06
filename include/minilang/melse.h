#pragma once

#include <minilang/mstatement.h>
#include <minilang/mscope.h>

namespace mini {
    class MElse : public mini::MScope, public mini::MStatement {
    public:
        /**
         * @see mini::MScope::prettify
         */
        std::string prettify(int indent);
    };
}