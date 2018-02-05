#pragma once

#include <minilang/mstatement.h>
#include <minilang/midentifier.h>

namespace mini {
    class MRead : public mini::MStatement {
    private:

        // Read into this identifier
        mini::MIdentifier* m_identifier = nullptr;

    public:
        MRead(mini::MIdentifier* identifier) : m_identifier(identifier){}

        /**
         * Get identifier
         * @return identifier pointer
         */
        mini::MIdentifier* getIdentifier() const {return m_identifier;}
    };
}