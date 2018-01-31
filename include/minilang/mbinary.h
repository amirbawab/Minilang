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

        /**
         * Set left expression
         * @param left
         */
        void setLeft(std::shared_ptr<MExpression> left) {m_left = left;}

        /**
         * Set right expression
         * @param right
         */
        void setRight(std::shared_ptr<MExpression> right) {m_right = right;}

        /**
         * Get left expression
         * @return left expression
         */
        std::shared_ptr<mini::MExpression> getLeft() const {return m_left;}

        /**
         * Get right expression
         * @return right expression
         */
        std::shared_ptr<mini::MExpression> getRight() const {return m_right;}
    };
}
