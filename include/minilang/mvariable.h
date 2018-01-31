#pragma once

#include <minilang/mtype.h>
#include <minilang/mexpression.h>
#include <memory>

namespace mini {
    class MVariable {
    private:

        // Variable type
        mini::TYPE m_type;

        // Variable name
        std::string m_name;

        // Variable expression
        mini::MExpression* m_expression;

    public:

        /**
         * Get varibale type
         * @return enum
         */
        mini::TYPE getType() const { return m_type; }

        /**
         * Get variable expression
         * @return expression
         */
        mini::MExpression* getExpression() { return m_expression; }

        /**
         * Get varibale name
         * @return string name
         */
        std::string getName() const {return m_name;}
    };
}
