#pragma once

#include <minilang/mexpression.h>
#include <memory>

namespace mini {
    class MUnary : public MExpression {
    private:

        // The only operand
        mini::MExpression* m_operand;

        // operator value
        std::string m_operator;

    public:
        /**
         * @see mini::MExpression::evalType
         */
        virtual mini::TYPE evalType();

        /**
         * Set operand for the unary expression
         * @param operand
         */
        void setOperand(mini::MExpression* operand) {m_operand = operand;}
    };
}
