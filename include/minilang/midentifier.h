#pragma once

#include <minilang/mvariable.h>

namespace mini {
    class MIdentifer : public mini::MExpression {
    private:

        // Original variable this identifier refers to
        mini::MVariable* m_variable = nullptr;
    public:

        /**
         * Get original vairable
         * @return
         */
        mini::MVariable* getVariable() const {return m_variable;}

        /**
         * @see mini::MExpression::evalTYpe
         */
        virtual mini::TYPE evalType();

        /**
         * @see mini::MExpression::prettify
         */
        virtual std::string prettify();
    };
}
