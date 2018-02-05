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

        // Variable expression value
        mini::MExpression* m_expression = nullptr;

    public:

        /**
         * Get varibale type
         * @return enum
         */
        mini::TYPE getType() const { return m_type; }

        /**
         * Get varibale name
         * @return string name
         */
        std::string getName() const {return m_name;}

        /**
         * Set variable expression value
         * @param expression
         */
        void setExpression(mini::MExpression* expression) {m_expression = expression;}

        /**
         * Get expression
         * @return expression
         */
        mini::MExpression* getExpression() const { return m_expression; }
    };
}
