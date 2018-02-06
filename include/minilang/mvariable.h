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
         * Get varibale type
         * @return enum
         */
        mini::TYPE getType() const { return m_type; }

        /**
         * Get identifier
         * @return identifier
         */
        mini::MIdentifier* getIdentifier() const { return m_identifier; }
    };
}
