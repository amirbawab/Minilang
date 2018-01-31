#pragma once

#include <memory>
#include <minilang/mtype.h>
#include <minilang/mexpression.h>

namespace mini {
    class MBinary : public MExpression {
    private:
        // Left operand
        MExpression* m_left;

        // Right operand
        MExpression* m_right;

        // operator value
        std::string m_operator;

    public:

        /**
         * @see mini::MExpression::evalType
         */
        virtual mini::TYPE evalType();

        /**
         * Set left expression
         * @param left
         */
        void setLeft(MExpression* left) {m_left = left;}

        /**
         * Set right expression
         * @param right
         */
        void setRight(MExpression* right) {m_right = right;}

        /**
         * Get left expression
         * @return left expression
         */
        mini::MExpression* getLeft() const {return m_left;}

        /**
         * Get right expression
         * @return right expression
         */
        mini::MExpression* getRight() const {return m_right;}
    };
}
