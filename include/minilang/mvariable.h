#pragma once

#include <minilang/mtype.h>
#include <minilang/midentifier.h>
#include <memory>

namespace mini {
    class MVariable {
    private:

        // Variable type
        mini::TYPE m_type;

        // Variable identifier
        mini::MIdentifier* m_identifier = nullptr;

    public:
        MVariable(mini::MIdentifier* identifier) : m_identifier(identifier){}

        /**
         * Set type
         * @param type
         */
        void setType(mini::TYPE type) {m_type = type;}

        /**
         * Get varibale type
         * @return enum
         */
        mini::TYPE getType() const { return m_type; }

        /**
         * Get identifier
         * @return identifier
         */
        mini::MIdentifier* getIdentifier() const { return m_identifier; }

        /**
         * Prettify code
         * @return prettify code
         */
        std::string prettify(int indent);

        /**
         * Check if variable already
         */
        void checkExist();

        /**
         * Check type
         */
        void typeCheck();

        /**
         * Check if type is compatible
         */
        void compatibleExpr(mini::MExpression* expression);
    };
}
