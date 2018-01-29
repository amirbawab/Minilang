#pragma once

#include <memory>
#include <minilang/mtype.h>

namespace mini {

    /**
     * Expression representing a binary or a unary operation
     */
    class MExpression {
    public:
        /**
         * Specify the kind of the expression
         * A binary operation
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
            U_INTEGER,
            U_FLOAT,
            U_BOOLEAN,
            U_STRING,
            U_IDENTIFIER,
            U_MINUS,
            U_NOT
        };

    private:
        // Left operand
        std::shared_ptr<MExpression> m_left;

        // Right operand
        std::shared_ptr<MExpression> m_right;

        // Kind of the expression
        KIND m_kind = mini::MExpression::KIND::UNDEFINED;

        // Operator value
        std::string m_operator;

    public:
        MExpression(){};

        /**
         * Check if expression is composed of only one element
         * e.g. string, integer, float and indetifier
         * @return true if expression is atomic
         */
        bool isAtomic() const;

        /**
         * Check if expression is unary
         * @return true if expression is unary
         */
        bool isUnary() const;

        /**
         * Set the kind of the expression
         * @param kind
         */
        void setKind(mini::MExpression::KIND kind) { m_kind = kind; }

        /**
         * Evaluate the type of the expression
         */
        mini::TYPE evalType();
    };
}
