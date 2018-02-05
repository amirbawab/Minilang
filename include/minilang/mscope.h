#pragma once

#include <minilang/mstatement.h>
#include <vector>

namespace mini {
    class MScope {
    protected:

        // Keep track of nested scopes
        std::vector<mini::MScope*> m_scopes;

        // While loop statements
        std::vector<mini::MStatement*> m_statements;
    public:

        /**
         * Add statement to this scope
         * @param statement
         */
        void addStatement(mini::MStatement* statement);

        /**
         * Get statements
         * @return vector of statements
         */
        std::vector<mini::MStatement*> getStatements() const { return m_statements; }
    };
}
