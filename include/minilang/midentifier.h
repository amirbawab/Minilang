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

        // Line number
        int m_line;

    public:
        MIdentifier(std::string name, int line) : m_name(name), m_line(line) {}

        ~MIdentifier();

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
         * Get variable name in C
         * @return string name
         */
        std::string getCName();

        /**
         * @see mini::MExpression::evalType
         */
        mini::TYPE evalType();

        /**
         * @see mini::MExpression::prettify
         */
        std::string prettify();

        /**
         * @see mini::MExpression::toC
         */
        std::string toC();

        /**
         * @see mini::MStatement::prettify
         */
        std::string prettify(int indent);

        /**
         * @see mini::MStatement::toC
         */
        std::string toC(int indent);

        /**
         * @see mini::MStatement::typeCheck
         */
        void typeCheck();

        /**
         * Link to referece variable
         */
        void linkVariable();

        /**
         * Get line number
         * @return line number
         */
        int getLine() { return m_line; }
    };
}
