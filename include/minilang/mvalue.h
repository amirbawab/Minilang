#pragma once

#include <minilang/mexpression.h>

namespace mini {
    template <class T>
    class MValue : public MExpression {
    private:

        // Value of the expression
        T m_value;

        // Kind of the expression
        MExpression::KIND m_kind = MExpression::UNDEFINED;

    public:
        /**
         * Construct an atomic expression
         * @param value
         * @param kind
         */
        MValue(T value, MExpression::KIND kind) : m_value(value), m_kind(kind){}

        /**
         * Get value of the epxression
         * @return
         */
        T getValue() const { return m_value; }

        /**
         * @see mini::MExpression::evalType
         */
        TYPE evalType();
    };
}
