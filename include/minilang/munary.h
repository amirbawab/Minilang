#pragma once

#include <minilang/mexpression.h>
#include <memory>

namespace mini {
    class MUnary : public MExpression {
    private:

        // The only operand
        std::shared_ptr<mini::MExpression> m_operand;

        // operator value
        std::string m_operator;

    public:
        /**
         * @see mini::MExpression::evalType
         */
        virtual mini::TYPE evalType();
    };
}
