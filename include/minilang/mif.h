#pragma once

#include <minilang/mstatement.h>
#include <minilang/mscope.h>
#include <minilang/mexpression.h>

namespace mini {
    class MIf : public mini::MScope, public mini::MStatement {
    private:
        // If condition
        mini::MExpression* m_condition = nullptr;
    public:
        MIf(mini::MExpression* condition) : m_condition(condition){}

        /**
         * Get if statement condition
         * @return condition
         */
        mini::MExpression* getCondition() const { return m_condition;}
    };
}