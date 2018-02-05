#pragma once

#include <minilang/mtype.h>
#include <minilang/midentifier.h>
#include <memory>

namespace mini {
    class MVariable {
    private:

        // Variable type
        mini::TYPE m_type;

        // Variable name
        std::string m_name;

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
         * Get varibale name
         * @return string name
         */
        std::string getName() const {return m_name;}

        /**
         * Get identifier
         * @return identifier
         */
        mini::MIdentifier* getIdentifier() const { return m_identifier; }
    };
}
