#pragma once

#include <minilang/mstatement.h>
#include <minilang/mscope.h>
#include <minilang/mexpression.h>

namespace mini {
    class MIf : public mini::MScope, public mini::MStatement {
    private:
        // If condition
        mini::MExpression* m_condition = nullptr;

        // Else statement
        mini::MStatement* m_else = nullptr;
    public:
        MIf(mini::MExpression* condition) : m_condition(condition){}

        /**
         * Get if statement condition
         * @return condition
         */
        mini::MExpression* getCondition() const { return m_condition;}

        /**
         * Set else statement
         * @param elseStmt
         */
        void setElse(mini::MStatement* elseStmt) {m_else = elseStmt;}

        /**
         * Get else statement
         * @return else statement
         */
        mini::MStatement* getElse() const {return m_else;}

        /**
         * @see mini::MScope::prettify
         */
        std::string prettify(int indent);
    };
}