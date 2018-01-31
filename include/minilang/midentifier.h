#pragma once

#include <minilang/mvariable.h>

namespace mini {
    class MIdentifier : public mini::MExpression {
    private:

        // Original variable this identifier refers to
        mini::MVariable* m_variable = nullptr;
    public:
        MIdentifier(MVariable* variable) : m_variable(variable){}

        /**
         * Get original vairable
         * @return
         */
        mini::MVariable* getVariable() const {return m_variable;}

        /**
         * @see mini::MExpression::evalType
         */
        virtual mini::TYPE evalType();

        /**
         * @see mini::MExpression::prettify
         */
        virtual std::string prettify();
    };
}
