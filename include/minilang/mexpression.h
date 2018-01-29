#pragma once

#include <memory>
#include <minilang/mkind.h>

namespace mini {

    /**
     * Expression representing a binary or a unary operation
     */
    class MExpression {
    private:
        // Left operand
        std::shared_ptr<MExpression> m_left;

        // Right operand
        std::shared_ptr<MExpression> m_right;

        // Type of the expression
        mini::MExpression::TYPE m_type = mini::MExpression::UNDEFINED;

        // Kind of the expression
        mini::KIND m_kind = mini::KIND::UNDEFINED;

    public:
        MExpression(){};

        /**
         * Specify the type of the expression
         * A binary operation
         */
        enum TYPE {
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
            U_NOT
        };

        /**
         * Check if expression is unary
         * @return true if expression is unary
         */
        bool isUnary() const;

        /**
         * Check if an expression is undefined
         * @return true if undefined
         */
        bool isUndefined() const;
    };
}
