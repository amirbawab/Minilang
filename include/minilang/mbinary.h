#pragma once

#include <memory>
#include <minilang/mtype.h>
#include <minilang/mexpression.h>

namespace mini {
    class MBinary : MExpression {
    private:
        // Left operand
        std::shared_ptr<MExpression> m_left;

        // Right operand
        std::shared_ptr<MExpression> m_right;

        // operator value
        std::string m_operator;

    public:

        /**
         * Set the kind of the expression
         * @param kind
         */
        void setKind(KIND kind) { m_kind = kind; }

        /**
         * @see mini::MExpression::evalType
         */
        virtual mini::TYPE evalType();
    };
}
