#pragma once

#include <minilang/mstatement.h>
#include <minilang/mexpression.h>

namespace mini {
    class MPrint : public mini::MStatement {
    private:

        // Expression to print
        mini::MExpression* m_expression = nullptr;

    public:
        MPrint(mini::MExpression* expression) : m_expression(expression){}

        /**
         * Get print expression
         * @return expression pointer
         */
        MExpression* getExpression() const {return m_expression;}

        /**
         * @see mini::MStatement::prettify
         */
        std::string prettify(int indent);
    };
}