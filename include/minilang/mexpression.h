#pragma once

#include <minilang/mtype.h>

namespace mini {
    class MExpression {
    public:
        /**
         * Specify the kind of the expression
         */
        enum KIND {
            UNDEFINED,
            B_PLUS,
            B_MINUS,
            B_TIMES,
            B_DIVIDE,
            B_AND,
            B_OR,
            B_IS_EQUAL,
            B_IS_NOT_EQUAL,
            U_MINUS,
            U_NOT,
            V_INTEGER,
            V_FLOAT,
            V_BOOLEAN,
            V_STRING,
            V_IDENTIFIER
        };

        /**
         * Evaluate the type of the expression
         */
        virtual mini::TYPE evalType()=0;

        protected:
            // Kind of the expression
            KIND m_kind = KIND::UNDEFINED;
    };
}
