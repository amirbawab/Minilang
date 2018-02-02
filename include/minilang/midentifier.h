#pragma once

#include <minilang/mvariable.h>

namespace mini {
    class MIdentifier : public mini::MExpression {
    private:

        // Original variable this identifier refers to
        mini::MVariable* m_variable = nullptr;

        // Expression assigned to the identifier
        mini::MExpression* m_expression = nullptr;
    public:
        MIdentifier(MVariable* variable) : m_variable(variable){}

        /**
         * Get original vairable
         * @return
         */
        mini::MVariable* getVariable() const {return m_variable;}

        /**
         * Get expression assigned to the identifier
         * @return expression
         */
        mini::MExpression* getExpression() const {return m_expression;}

        /**
         * Assign expression to identifier
         * @param expression
         */
        void setExpression(mini::MExpression* expression) { m_expression = expression;}

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
