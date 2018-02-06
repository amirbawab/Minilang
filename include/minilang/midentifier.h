#pragma once

#include <minilang/mexpression.h>
#include <minilang/mstatement.h>

namespace mini {
    class MVariable;
    class MIdentifier : public mini::MExpression, public mini::MStatement {
    private:

        // Original variable this identifier refers to
        mini::MVariable* m_variable = nullptr;

        // Expression assigned to the identifier
        mini::MExpression* m_expression = nullptr;

        // Identifier name
        std::string m_name;

    public:
        MIdentifier(std::string name) : m_name(name) {}

        /**
         * Get original vairable
         * @return
         */
        mini::MVariable* getVariable() const {return m_variable;}

        /**
         * Set reference variable for this identifier
         * @param variable
         */
        void setVariable(mini::MVariable* variable) {m_variable = variable;}

        /**
         * Get expression assigned to the identifier
         * @return expression
         */
        mini::MExpression* getExpression() const {return m_expression;}

        /**
         * Assign expression to identifier
         * @param expression
         */
        void setExpression(mini::MExpression* expression) {m_expression = expression;}

        /**
         * Get varibale name
         * @return string name
         */
        std::string getName() const {return m_name;}

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
