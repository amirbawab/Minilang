#pragma once

#include <minilang/mscope.h>
#include <minilang/mexpression.h>
#include <minilang/mstatement.h>
#include <vector>

namespace mini {
    class MWhile : public mini::MScope, public mini::MStatement {
    private:

        // While loop condition
        mini::MExpression* m_condition = nullptr;
    public:
        MWhile(mini::MExpression* condition) : m_condition(condition){}

        /**
         * Get if statement condition
         * @return condition
         */
        mini::MExpression* getCondition() const { return m_condition;}

        /**
         * @see mini::MScope::prettify
         */
        std::string prettify(int indent);
    };
}

