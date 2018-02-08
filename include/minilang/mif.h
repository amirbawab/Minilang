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

        ~MIf();

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

        /**
         * @see mini::MScope::toC
         */
        std::string toC(int indent);

        /**
         * @see mini::MStatement::typeCheck
         */
        void typeCheck();
    };
}